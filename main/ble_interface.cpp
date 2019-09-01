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
}

void BleInterface::OnSensorStateChange(const SensorManager& sensorManager, Sensor sensor) {
	auto& t_0 = sensorManager.GetHistory()[0];
	auto& keyState = t_0.keyState[sensor];
	auto& keyPos = t_0.kinematic.position[sensor];
	auto& keyVel = t_0.kinematic.velocity[sensor];
	auto& keyAcc = t_0.kinematic.acceleration[sensor];
	if (keyState.pressed) {
		fmt::print("key[{:2d}] down  pos: {:7.2f} vel: {:7.2f} acc: {:7.2f}\n", static_cast<size_t>(sensor), keyPos, keyVel, keyAcc);
	} else {
		fmt::print("key[{:2d}] up    pos: {:7.2f} vel: {:7.2f} acc: {:7.2f}\n", static_cast<size_t>(sensor), keyPos, keyVel, keyAcc);
	}
}


} // namespace opkey
