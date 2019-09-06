#include "fmt.h"
#include "application.h"
#include "sensor_manager.h"

#include "ble_interface.h"


namespace opkey {


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


BleInterface::BleInterface(Application& application)
	: onTickConnection(application.GetOnTickSink().connect<&BleInterface::OnTick>(*this))
	, onModeChangeConnection(application.GetOnModeChangeSink().connect<&BleInterface::OnModeChange>(*this))
	, onSensorStateChangeConnection{}
{ }

void BleInterface::OnTick() {
	OPKEY_PROFILE_FUNCTION();
	//TODO if (not midiPacketGenerator.empty()) {
	//TODO 	midiPacketGenerator.flush();
	//TODO }

	//if (elapsed > continousStatusFps) {
	//	send pedal values
	//}
	//static int i = 0;
	//if (++i % 200 == 0) {
	//	blecfg::midiPacketSend = { 0x80, 0x80, 0x90, 0x3c, 0x7f };
	//	bleInstance.template NotifyAll<blecfg::MidiChrUuid>();
	//} else if (i % 200 == 1) {
	//	blecfg::midiPacketSend = { 0x80, 0x80, 0x80, 0x3c, 0x00 };
	//	bleInstance.template NotifyAll<blecfg::MidiChrUuid>();
	//}
}

void BleInterface::OnModeChange(Mode oldMode, Mode newMode) {
	switch (newMode) {
		case Mode::NormalOperation:
			onSensorStateChangeConnection = Application::instance->GetOnSensorStateChangeSink().connect<&BleInterface::OnSensorStateChange>(*this);
			break;

		default:
			onSensorStateChangeConnection = entt::scoped_connection{};
			break;
	}
}

void BleInterface::OnSensorStateChange(const SensorManager& sensorManager, Sensor sensor) {
	auto& t_0 = sensorManager.GetHistory()[0];
	auto& keyState = t_0.keyState[sensor];
	auto& keyPos = t_0.kinematic.position[sensor];
	auto& keyVel = t_0.kinematic.velocity[sensor];
	auto& keyAcc = t_0.kinematic.acceleration[sensor];
	if (keyState.pressed) {
		// TODO only accumulate midi buffer, send on tick or second fin event?
		fmt::print("key[{:2d}] down  pos: {:7.2f} vel: {:7.2f} acc: {:7.2f}\n", static_cast<size_t>(sensor), keyPos, keyVel, keyAcc);
		auto v = ((keyVel - 2.0) / 4.0);
		if (v < 0)
			v = 0;
		else if (v > 1)
			v = 1;

		// TODO midiPacketGenerator.append(0x90, static_cast<uint8_t>(0x15 + sensor.GetKeyIndex()), static_cast<uint8_t>(0x7f * v));
		blecfg::midiPacketSend = { 0x80, 0x80, 0x90, static_cast<uint8_t>(0x15 + sensor.GetKeyIndex()), static_cast<uint8_t>(0x7f * v) };
		bleInstance.template NotifyAll<blecfg::MidiChrUuid>();
	} else {
		//fmt::print("key[{:2d}] up    pos: {:7.2f} vel: {:7.2f} acc: {:7.2f}\n", static_cast<size_t>(sensor), keyPos, keyVel, keyAcc);
		blecfg::midiPacketSend = { 0x80, 0x80, 0x80, static_cast<uint8_t>(0x15 + sensor.GetKeyIndex()), 0x00 };
		bleInstance.template NotifyAll<blecfg::MidiChrUuid>();
	}
}


} // namespace opkey
