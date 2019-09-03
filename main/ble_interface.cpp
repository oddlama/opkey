#include "fmt.h"
#include "application.h"
#include "sensor_manager.h"

#include "ble_interface.h"


namespace opkey {


BleInterface::BleInterface(Application& application)
	: onTickConnection(application.GetOnTickSink().connect<&BleInterface::OnTick>(*this))
	, onSensorStateChangeConnection(application.GetOnSensorStateChangeSink().connect<&BleInterface::OnSensorStateChange>(*this))
{ }

void BleInterface::OnTick() {
	OPKEY_PROFILE_FUNCTION();
	//if (elapsed > continousStatusFps) {
	//	send pedal values
	//}
	//static int i = 0;
	//if (++i % 200 == 0) {
	//	blecfg::midiPacket = { 0x80, 0x80, 0x90, 0x3c, 0x7f };
	//	bleInstance.template NotifyAll<blecfg::MidiChrUuid>();
	//} else if (i % 200 == 1) {
	//	blecfg::midiPacket = { 0x80, 0x80, 0x80, 0x3c, 0x00 };
	//	bleInstance.template NotifyAll<blecfg::MidiChrUuid>();
	//}
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
		blecfg::midiPacket = { 0x80, 0x80, 0x90, static_cast<uint8_t>(0x15 + sensor.GetKeyIndex()), static_cast<uint8_t>(0x7f * v) };
		bleInstance.template NotifyAll<blecfg::MidiChrUuid>();
	} else {
		//fmt::print("key[{:2d}] up    pos: {:7.2f} vel: {:7.2f} acc: {:7.2f}\n", static_cast<size_t>(sensor), keyPos, keyVel, keyAcc);
		blecfg::midiPacket = { 0x80, 0x80, 0x80, static_cast<uint8_t>(0x15 + sensor.GetKeyIndex()), 0x00 };
		bleInstance.template NotifyAll<blecfg::MidiChrUuid>();
	}
}


} // namespace opkey
