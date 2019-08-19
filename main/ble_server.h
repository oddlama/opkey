#pragma once

#include "entt.h"
#include "sensor.h"


namespace OpKey {


class Application;
class SensorManager;

class BleServer {
public:
	BleServer(Application& application);

	BleServer(const BleServer&) = default;
	BleServer(BleServer&&) = default;
	BleServer& operator=(const BleServer&) = delete;
	BleServer& operator=(BleServer&&) = delete;

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
