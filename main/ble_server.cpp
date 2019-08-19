#include "ble_server.h"
#include "application.h"
#include "sensor_manager.h"


namespace OpKey {


BleServer::BleServer(Application& application)
	: onTickConnection(application.GetOnTickSink().connect<&BleServer::OnTick>(*this))
	, onSensorStateChangeConnection(application.GetOnSensorStateChangeSink().connect<&BleServer::OnSensorStateChange>(*this))
{ }

void BleServer::OnTick() {
	OPKEY_PROFILE_FUNCTION();
}

void BleServer::OnSensorStateChange(const SensorManager& sensorManager, Sensor sensor) {
	auto& h0 = sensorManager.GetHistory()[0];
	auto& keyState = h0.keyState[sensor];
	auto& keyPos = h0.kinematic.position[sensor];
	auto& keyVel = h0.kinematic.velocity[sensor];
	auto& keyAcc = h0.kinematic.acceleration[sensor];
	if (keyState.pressed) {
		fmt::print("key[{:2d}] down  pos: {:7.2f} vel: {:7.2f} acc: {:7.2f}\n", static_cast<size_t>(sensor), keyPos, keyVel, keyAcc);
	} else {
		fmt::print("key[{:2d}] up    pos: {:7.2f} vel: {:7.2f} acc: {:7.2f}\n", static_cast<size_t>(sensor), keyPos, keyVel, keyAcc);
	}
}


} // namespace OpKey
