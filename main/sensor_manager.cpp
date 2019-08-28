#include "sensor_manager.h"
#include "application.h"


namespace opkey {


SensorManager::SensorManager(Application& application)
	: onTickConnection(application.GetOnTickSink().connect<&SensorManager::OnTick>(*this))
{
	// Initialize history with valid data
	SensorData data{};
	adcController.Read(data, 512);
	history.Init(data);
}


void SensorManager::OnTick() {
	OPKEY_PROFILE_FUNCTION();
	SensorData data{};
	// TODO settings for samples
	adcController.Read(data, 8);
	history.Append(data);

	// Notify listeners if a key state has changed
	const auto& t_0 = history[0];
	Sensor::ForEachKey([&](Sensor key) {
		if (t_0.keyState[key].changed) {
			onSensorStateChangeSignal.publish(*this, key);
		}
	});
}


} // namespace opkey
