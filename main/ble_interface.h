#pragma once

#include "entt.h"
#include "sensor.h"


namespace OpKey {


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

	//void OnKeyPressed(Key key, double velocity, ) {
	//}
	//void OnKeyReleased(Key key, ) {
	//}

private:
	entt::scoped_connection onTickConnection;
	entt::scoped_connection onSensorStateChangeConnection;
};


} // namespace OpKey
