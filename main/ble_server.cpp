#include "ble_server.h"
#include "application.h"


namespace OpKey {


BleServer::BleServer(Application& application)
	: onTickConnection(application.GetOnTickSink().connect<&BleServer::OnTick>(*this))
	, onSensorStateChangeConnection(application.GetOnSensorStateChangeSink().connect<&BleServer::OnSensorStateChange>(*this))
{ }

void BleServer::OnTick() {
	OPKEY_PROFILE_FUNCTION();
}

void BleServer::OnSensorStateChange(const SensorManager& sensorManager, Sensor sensor) {
}


} // namespace OpKey
