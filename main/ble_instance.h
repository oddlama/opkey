#pragma once

#include "fmt.h"

#include "ble_meta.h"
#include "ble_uuid.h"
#include "ble_server.h"
#include "ble_instance.h"

#include <esp_err.h>
#include <esp_nimble_hci.h>
#include <nimble/nimble_port.h>
#include <nimble/nimble_port_freertos.h>
#include <host/ble_hs.h>
#include <host/ble_uuid.h>
#include <host/util/util.h>
#include <services/gap/ble_svc_gap.h>
#include <services/gatt/ble_svc_gatt.h>


namespace opkey::ble {


extern "C" {
	void ble_store_config_init();
}


static std::string AddrToString(uint8_t val[6]) {
	return fmt::format("{:02x}:{:02x}:{:02x}:{:02x}:{:02x}:{:02x}", val[0], val[1], val[2], val[3], val[4], val[5]);
}

static void BlePrintConnDesc(ble_gap_conn_desc& desc) {
	esp::logi("handle={:d} our_ota_addr_type={:d} our_ota_addr={}"
			, desc.conn_handle, desc.our_ota_addr.type
			, AddrToString(desc.our_ota_addr.val));
	esp::logi("our_id_addr_type={:d} our_id_addr={}"
			, desc.our_id_addr.type
			, AddrToString(desc.our_id_addr.val));
	esp::logi("peer_ota_addr_type={:d} peer_ota_addr={}"
			, desc.peer_ota_addr.type
			, AddrToString(desc.peer_ota_addr.val));
	esp::logi("peer_id_addr_type={:d} peer_id_addr={}"
			, desc.peer_id_addr.type
			, AddrToString(desc.peer_id_addr.val));
	esp::logi("conn_itvl={:d} conn_latency={:d} supervision_timeout={:d} encrypted={} authenticated={} bonded={}\n"
			, desc.conn_itvl
			, desc.conn_latency
			, desc.supervision_timeout
			, static_cast<bool>(desc.sec_state.encrypted)
			, static_cast<bool>(desc.sec_state.authenticated)
			, static_cast<bool>(desc.sec_state.bonded));
}


static_assert(ESP_OK == 0, "This module relies on the value of ESP_OK to be 0");


static inline size_t bleInitialized = false;


static void NimbleHostTask(void* param) {
	esp::logi("NimbleHostTask started");

	// This function will return only when nimble_port_stop() is executed
	nimble_port_run();
	nimble_port_freertos_deinit();
}


template<typename ServerType>
class Instance {
public:
	explicit Instance(const char* name)
		: name(name)
	{
		if (bleInitialized) {
			throw std::runtime_error("Cannot create multiple instances of ble::Instance.");
		}

		instance = this;
		esp::check(esp_nimble_hci_and_controller_init(), "esp_nimble_hci_and_controller_init()");
		nimble_port_init();

		// Initialize the NimBLE host configuration.
		ble_hs_cfg.reset_cb = StaticOnReset;
		ble_hs_cfg.sync_cb = StaticOnSync;
		//ble_hs_cfg.gatts_register_cb = BleGattRegister;
		ble_hs_cfg.store_status_cb = ble_store_util_status_rr;

		ble_hs_cfg.sm_io_cap = BLE_SM_IO_CAP_NO_IO;
		ble_hs_cfg.sm_bonding = true;
		ble_hs_cfg.sm_mitm = true;
		ble_hs_cfg.sm_sc = true;
		ble_hs_cfg.sm_our_key_dist = BLE_SM_PAIR_KEY_DIST_ENC;
		ble_hs_cfg.sm_their_key_dist = BLE_SM_PAIR_KEY_DIST_ENC;

		ble_svc_gap_init();
		ble_svc_gatt_init();

		for (const auto& s : ServerType::nimbleGattServiceDefinitions) {
			if (s.type == 0) { break; }
			esp::logi("service:");
			esp::logi("- type: {}", s.type);
			esp::logi("- uuid: {} {:02x}{:02x}", (void*)s.uuid, ((char*)s.uuid)[1], ((char*)s.uuid)[2]);
			esp::logi("- characteristics: {}", (void*)s.characteristics);
			auto* c = s.characteristics;
			while (c && c->uuid) {
				esp::logi("    characteristic:");
				esp::logi("    - uuid: {}", (void*)c->uuid, ((char*)c->uuid)[1], ((char*)c->uuid)[2]);
				esp::logi("    - access_cb: {}", (void*)c->access_cb);
				esp::logi("    - flags: {}", c->flags);
				++c;
			}
		}
		esp::check(ble_gatts_count_cfg(ServerType::nimbleGattServiceDefinitions.data()), "ble_gatts_count_cfg()");
		esp::check(ble_gatts_add_svcs(ServerType::nimbleGattServiceDefinitions.data()), "ble_gatts_add_svcs()");
		esp::check(ble_svc_gap_device_name_set(name), "ble_svc_gap_device_name_set()");

		ble_store_config_init();
		nimble_port_freertos_init(NimbleHostTask);
	}

	~Instance() noexcept {
		nimble_port_stop();
		bleInitialized = false;
	}

	Instance(const Instance&) = delete;
	Instance(Instance&&) = delete;
	Instance& operator=(const Instance&) = delete;
	Instance& operator=(Instance&&) = delete;

private:
	void EnableAdvertising() {
		// Set the advertisement data included in our advertisements:
		//   - Flags (indicates advertisement type and other general info).
		//   - Advertising tx power.
		//   - Device name.
		//   - 16-bit service UUIDs (alert notifications).
		// Advertise two flags:
		//   - Discoverability in forthcoming advertisement (general)
		//   - BLE-only (BR/EDR unsupported).
		ble_hs_adv_fields fields{};
		fields.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP;
		// Indicate that the TX power level field should be included; have the
		// stack fill this value automatically.  This is done by assigning the
		// special value BLE_HS_ADV_TX_PWR_LVL_AUTO.
		fields.tx_pwr_lvl_is_present = 1;
		fields.tx_pwr_lvl = BLE_HS_ADV_TX_PWR_LVL_AUTO;

		// TODO const cast?!
		fields.name = const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(name));
		fields.name_len = strlen(name);
		fields.name_is_complete = 1;

		fields.uuids16 = const_cast<ble_uuid16_t*>(&Uuid16<0x1811>::nimbleUuid);
		fields.num_uuids16 = 1;
		fields.uuids16_is_complete = 1;

		if (auto rc = ble_gap_adv_set_fields(&fields); rc != 0) {
			esp::loge("error setting advertisement data; rc={:d}\n", rc);
			return;
		}

		// Begin advertising.
		ble_gap_adv_params advertisingParams{};
		advertisingParams.conn_mode = BLE_GAP_CONN_MODE_UND;
		advertisingParams.disc_mode = BLE_GAP_DISC_MODE_GEN;

		auto rc = ble_gap_adv_start(ownAddressType, nullptr, BLE_HS_FOREVER,
				&advertisingParams, StaticOnGapEvent, this);
		if (rc != 0) {
			esp::loge("error enabling advertisement; rc={:d}\n", rc);
			return;
		}
	}

	void OnReset(int reason) {
		esp::loge("Resetting state; reason={:d}\n", reason);
		inSync = false;
	}

	void OnSync() {
		assert(ble_hs_util_ensure_addr(0) == 0);

		// Figure out address to use while advertising (no privacy for now)
		if (auto rc = ble_hs_id_infer_auto(0, &ownAddressType); rc != 0) {
			esp::loge("error determining address type; rc={:d}\n", rc);
			return;
		}

		inSync = true;

		// Printing ADDR
		std::array<uint8_t, 6> addrVal{};
		ble_hs_id_copy_addr(ownAddressType, addrVal.data(), nullptr);
		esp::logi("Device Address: {}\n", AddrToString(addrVal.data()));

		// Begin advertising
		EnableAdvertising();
	}

	/**
	 * The nimble host executes this callback when a GAP event occurs.  The
	 * application associates a GAP event callback with each connection that forms.
	 * bleprph uses the same callback for all connections.
	 *
	 * @param event   The type of event being signalled.
	 * @param ctxt    Various information pertaining to the event.
	 * @param arg     Application-specified argument; unused by
	 *                  bleprph.
	 *
	 * @return        0 if the application successfully handled the
	 *                  event; nonzero on failure.  The semantics
	 *                  of the return code is specific to the
	 *                  particular GAP event being signalled.
	 */
	int OnGapEvent(ble_gap_event* event) {
		ble_gap_conn_desc desc;
		int rc;
		// TODO clean variables to local

		switch (event->type) {
			case BLE_GAP_EVENT_CONNECT:
				// A new connection was established or a connection attempt failed.
				esp::logi("connection {:s}; status={:d} ",
						event->connect.status == 0 ? "established" : "failed",
						event->connect.status);
				if (event->connect.status == 0) {
					rc = ble_gap_conn_find(event->connect.conn_handle, &desc);
					assert(rc == 0);
					BlePrintConnDesc(desc);
				}

				if (event->connect.status != 0) {
					// Connection failed; resume advertising.
					EnableAdvertising();
				}
				return 0;

			case BLE_GAP_EVENT_DISCONNECT:
				esp::logi("disconnect; reason={:d} ", event->disconnect.reason);
				BlePrintConnDesc(event->disconnect.conn);

				// Connection terminated; resume advertising.
				EnableAdvertising();
				return 0;

			case BLE_GAP_EVENT_CONN_UPDATE:
				// The central has updated the connection parameters.
				esp::logi("connection updated; status={:d} ",
						event->conn_update.status);
				rc = ble_gap_conn_find(event->connect.conn_handle, &desc);
				assert(rc == 0);
				// TODO clean asserts
				BlePrintConnDesc(desc);
				return 0;

			case BLE_GAP_EVENT_ADV_COMPLETE:
				esp::logi("advertise complete; reason={:d}",
						event->adv_complete.reason);
				EnableAdvertising();
				return 0;

			case BLE_GAP_EVENT_ENC_CHANGE:
				// Encryption has been enabled or disabled for this connection.
				esp::logi("encryption change event; status={:d} ",
						event->enc_change.status);
				rc = ble_gap_conn_find(event->connect.conn_handle, &desc);
				assert(rc == 0);
				BlePrintConnDesc(desc);
				return 0;

			case BLE_GAP_EVENT_SUBSCRIBE:
				esp::logi("subscribe event; conn_handle={:d} attr_handle={:d} "
						"reason={:d} prevn={} curn={} previ={} curi={}\n",
						event->subscribe.conn_handle,
						event->subscribe.attr_handle,
						event->subscribe.reason,
						static_cast<bool>(event->subscribe.prev_notify),
						static_cast<bool>(event->subscribe.cur_notify),
						static_cast<bool>(event->subscribe.prev_indicate),
						static_cast<bool>(event->subscribe.cur_indicate));
				return 0;

			case BLE_GAP_EVENT_MTU:
				esp::logi("mtu update event; conn_handle={:d} cid={:d} mtu={:d}\n",
						event->mtu.conn_handle,
						event->mtu.channel_id,
						event->mtu.value);
				return 0;

			case BLE_GAP_EVENT_REPEAT_PAIRING:
				// We already have a bond with the peer, but it is attempting to
				// establish a new secure link. This app sacrifices security for
				// convenience: just throw away the old bond and accept the new link.
				// TODO WHO THOUGHT THIS WOULD BE A GOOD IDEA FOR AN NIBLE-EXAMPLE?!

				// Delete the old bond. */
				rc = ble_gap_conn_find(event->repeat_pairing.conn_handle, &desc);
				assert(rc == 0);
				ble_store_util_delete_peer(&desc.peer_id_addr);

				// Return BLE_GAP_REPEAT_PAIRING_RETRY to indicate that the host should
				// continue with the pairing operation.
				return BLE_GAP_REPEAT_PAIRING_RETRY;

			case BLE_GAP_EVENT_PASSKEY_ACTION:
				esp::logi("PASSKEY_ACTION_EVENT started");
				ble_sm_io pkey = {0};
				int key = 0;

				if (event->passkey.params.action == BLE_SM_IOACT_DISP) {
					pkey.action = event->passkey.params.action;
					pkey.passkey = 123456; // This is the passkey to be entered on peer
					esp::logi("Enter passkey {:d} on the peer side", pkey.passkey);
					rc = ble_sm_inject_io(event->passkey.conn_handle, &pkey);
					esp::logi("ble_sm_inject_io result: {:d}\n", rc);
				} else if (event->passkey.params.action == BLE_SM_IOACT_NUMCMP) {
					esp::logi("Passkey on device's display: {:d}", event->passkey.params.numcmp);
					esp::logi("Accept or reject the passkey through console in this format -> key Y or key N");
					pkey.action = event->passkey.params.action;
					//if (scli_receive_key(&key)) {
					//	pkey.numcmp_accept = key;
					//} else {
					//	pkey.numcmp_accept = 0;
					//	esp::loge("Timeout! Rejecting the key");
					//}
					rc = ble_sm_inject_io(event->passkey.conn_handle, &pkey);
					esp::logi("ble_sm_inject_io result: {:d}\n", rc);
				} else if (event->passkey.params.action == BLE_SM_IOACT_OOB) {
					static uint8_t tem_oob[16] = {0};
					pkey.action = event->passkey.params.action;
					for (int i = 0; i < 16; i++) {
						pkey.oob[i] = tem_oob[i];
					}
					rc = ble_sm_inject_io(event->passkey.conn_handle, &pkey);
					esp::logi("ble_sm_inject_io result: {:d}\n", rc);
				} else if (event->passkey.params.action == BLE_SM_IOACT_INPUT) {
					esp::logi("Enter the passkey through console in this format-> key 123456");
					pkey.action = event->passkey.params.action;
					//if (scli_receive_key(&key)) {
					//	pkey.passkey = key;
					//} else {
					//	pkey.passkey = 0;
					//	esp::loge("Timeout! Passing 0 as the key");
					//}
					rc = ble_sm_inject_io(event->passkey.conn_handle, &pkey);
					esp::logi("ble_sm_inject_io result: {:d}\n", rc);
				}
				return 0;
		}

		return 0;
	}

private:
	static inline Instance* instance = nullptr;

	static void StaticOnReset(int reason) {
		instance->OnReset(reason);
	}

	static void StaticOnSync() {
		instance->OnSync();
	}

	static int StaticOnGapEvent(ble_gap_event* event, void* paramThis) {
		return static_cast<Instance*>(paramThis)->OnGapEvent(event);
	}

private:
	const char* name;
	uint8_t ownAddressType = 0;
	bool inSync = false;
};


} // namespace opkey::ble
