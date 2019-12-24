#include "fmt.h"
#include "application.h"
#include "sensor_manager.h"
#include "midi.h"

#include "ble_interface.h"


namespace opkey {


//TODO config
static constexpr const std::array<bool, 2> isContinuousPedal = { true, true };
static constexpr const double continuousPedalThreshold = 0.2;
static constexpr const double discretePedalThreshold = 0.2;


int OnPacketSendRequest(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context) {
	esp::logw("Unexpected request of opkey packet");
	return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
}

int OnPacketWrite(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context) {
	static PacketBuffer buf{};
	size_t packetLen = OS_MBUF_PKTLEN(context->om);
	if (packetLen > buf.size()) {
		return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
	}

	uint16_t countCopied;
	if (int err = ble_hs_mbuf_to_flat(context->om, buf.data(), buf.size(), &countCopied); err != 0) {
		return BLE_ATT_ERR_INSUFFICIENT_RES;
	}

	if (countCopied < 1) {
		esp::logw("Invalid packet received: size is 0");
		return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
	}

	PacketBuffer responseBuffer{};
	auto packetType = static_cast<PacketType>(buf[0]);
	size_t responseSize = HandlePacket(*Application::instance, packetType, buf, packetLen, responseBuffer);
	if (responseSize > buf.size()) {
		esp::loge("Response packet exceeds buffer length");
		return BLE_ATT_ERR_UNLIKELY;
	} else if (responseSize == 0) {
		return 0;
	}

	buf = responseBuffer;
	if (int err = os_mbuf_append(context->om, buf.data(), responseSize); err != 0) {
		return BLE_ATT_ERR_INSUFFICIENT_RES;
	}
	return 0;
}


int OnMidiPacket(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context) {
	static ble::Array<64> midiPacketRecv{};
	if (OS_MBUF_PKTLEN(context->om) > midiPacketRecv.size()) {
		return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
	}

	uint16_t countCopied;
	int err = ble_hs_mbuf_to_flat(context->om, midiPacketRecv.data(), midiPacketRecv.size(), &countCopied);
	if (countCopied == 0) {
		return 0;
	}

	midiPacketRecv.SetUsedSize(countCopied);
	if (err != 0) {
		return BLE_ATT_ERR_INSUFFICIENT_RES;
	}

	Application::instance->GetOnMidiRecvSignal().publish(midiPacketRecv);
	return 0;
}


BleInterface::BleInterface(Application& application)
	: onTickConnection(application.GetOnTickSink().connect<&BleInterface::OnTick>(*this))
	, onSensorStateChangeConnection(application.GetOnSensorStateChangeSink().connect<&BleInterface::OnSensorStateChange>(*this))
{ }

void BleInterface::OnTick() {
	OPKEY_PROFILE_FUNCTION();
	//TODO if (not midiPacketGenerator.empty()) {
	//TODO 	midiPacketGenerator.flush();
	//TODO }

	//static int64_t lastContinuousStatus = 0;

	//auto now = esp_timer_get_time();
	//// TODO reset all controllers c = 121, v = x
	//// TODO all notes off c = 123, v = 0
	//// TODO auto compensation in form of waitTilNextStatus = (2 * aim) - (elapsed since last)
	//if (now - lastContinuousStatus > 100000) {
	//	std::array<uint8_t, 2> pedalValues = {};
	//	Sensor::ForEachPedal([&](Sensor pedal) {
	//		const auto& state = Application::instance->GetSensorManager().GetLogicStates()[pedal];
	//		auto& value = pedalValues[pedal.GetPedalIndex()];

	//		if (isContinuousPedal[pedal.GetPedalIndex()]) {
	//			if (state.pos <= continuousPedalThreshold) {
	//				value = 0x00;
	//			} else {
	//				auto pos = (state.pos - continuousPedalThreshold) / (1.0 - continuousPedalThreshold);
	//				value = (pos >= 1.0) ? 0x7f : static_cast<uint8_t>(pos * 0x80);
	//			}
	//		} else {
	//			value = (state.pos < discretePedalThreshold) ? 0x00 : 0x7f;
	//		}
	//	});

	//	auto [ h0, h1 ] = midi::Header();
	//	blecfg::midiPacketSend = { h0, h1
	//		, midi::status::controlChange
	//		, midi::ccSensorSoft, pedalValues[0]
	//		, midi::ccSensorDamp, pedalValues[1]
	//		};

	//	bleInstance.template NotifyAll<blecfg::MidiChrUuid>();
	//	lastContinuousStatus = now;
	//}
}

void BleInterface::OnSensorStateChange(const SensorManager& sensorManager, Sensor sensor) {
	//TODO send midi reset all keys up when mode is changed!

	//TODO queue all midi events in a midi event queue, which is
	//simultaneously processed on vizu core (actual notifies)
	auto& state = sensorManager.GetLogicStates()[sensor];
	if (state.pressed) {
		uint8_t vel;
		if (state.pressVelocity >= 1.0) {
			vel = 0x7f;
		} else {
			vel = static_cast<uint8_t>(0x80 * state.pressVelocity);
		}

		// TODO temporary: prepend pedal messages
		std::array<uint8_t, 2> pedalValues = {};
		Sensor::ForEachPedal([&](Sensor pedal) {
			const auto& state = Application::instance->GetSensorManager().GetLogicStates()[pedal];
			auto& value = pedalValues[pedal.GetPedalIndex()];

			if (isContinuousPedal[pedal.GetPedalIndex()]) {
				if (state.pos <= continuousPedalThreshold) {
					value = 0x00;
				} else {
					auto pos = (state.pos - continuousPedalThreshold) / (1.0 - continuousPedalThreshold);
					value = (pos >= 1.0) ? 0x7f : static_cast<uint8_t>(pos * 0x80);
				}
			} else {
				value = (state.pos < discretePedalThreshold) ? 0x00 : 0x7f;
			}
		});

		auto [ h0, h1 ] = midi::Header();
		blecfg::midiPacketSend = { h0, h1
			, midi::status::controlChange
			, midi::ccSensorSoft, pedalValues[0]
			, midi::ccSensorDamp, pedalValues[1]
			, static_cast<uint8_t>(0x80 | ((h1 + 1u) & 0x7f))
			, midi::status::noteOn
			, static_cast<uint8_t>(0x15 + sensor.GetKeyIndex()), vel
			};
		bleInstance.template NotifyAll<blecfg::MidiChrUuid>();
	} else {
		auto [ h0, h1 ] = midi::Header();
		blecfg::midiPacketSend = { h0, h1
			, midi::status::noteOff
			, static_cast<uint8_t>(0x15 + sensor.GetKeyIndex()), 0x00
			};
		bleInstance.template NotifyAll<blecfg::MidiChrUuid>();
	}
}


} // namespace opkey
