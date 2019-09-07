#pragma once

#include "ble_instance.h"

#include "mode.h"
#include "entt.h"
#include "sensor.h"


namespace opkey {


int OnPacketSendRequest(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context);
int OnPacketWrite(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context);


namespace blecfg {

inline ble::Array<64> midiPacketSend{};
inline ble::Array<64> midiPacketRecv{};

using namespace ble;
namespace chr = ble::characteristic_options;
namespace svr = ble::server_options;

using MidiSvcUuid = Uuid128<0x03b80e5a, 0xede8, 0x4b33, 0xa751, 0x6ce34ec4c700>;
using MidiChrUuid = Uuid128<0x7772e5db, 0x3868, 0x4112, 0xa1a9, 0xf2669d106bf3>;
using OpKeySvcUuid = Uuid128<0x0b5487cd, 0x2237, 0x442f, 0x800e, 0x093b6032a160>;
using OpKeyChrUuid = Uuid128<0xd723c302, 0xf3e6, 0x4d5d, 0xa3cd, 0x11c1d3e0fc2d>;

using MidiService = Service
	< MidiSvcUuid
	, Characteristic
		< MidiChrUuid
		, chr::BindArray<&midiPacketSend, &midiPacketRecv>
		, chr::Notify
		, chr::WriteNoResponse
		>
	>;

using OpKeyService = Service
	< OpKeySvcUuid
	, Characteristic
		< OpKeyChrUuid
		, chr::ReadCallback<&OnPacketSendRequest>
		, chr::WriteCallback<&OnPacketWrite>
		, chr::Notify
		>
	>;

using Server = ble::Server
	< MidiService
	, OpKeyService
	, svr::AdvertiseUuid<MidiService::Uuid>
	>;

} // namespace blecfg


class Application;
class SensorManager;

class BleInterface {
public:
	BleInterface(Application& application);

	BleInterface(const BleInterface&) = default;
	BleInterface(BleInterface&&) = default;
	BleInterface& operator=(const BleInterface&) = delete;
	BleInterface& operator=(BleInterface&&) = delete;

	void OnTick();
	void OnSensorStateChange(const SensorManager& sensorManager, Sensor sensor);

private:
	entt::scoped_connection onTickConnection;
	entt::scoped_connection onSensorStateChangeConnection;

	ble::Instance<blecfg::Server> bleInstance{"OpKey"};
};


} // namespace opkey
