#include "sensor_manager.h"
#include "application.h"


namespace OpKey {


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
	const auto& h0 = history[0];
	for (size_t i = Sensor::KeyOffset; i < Sensor::KeyCount; ++i) {
		if (h0.keyState[i].changed) {
			onSensorStateChangeSignal.publish(*this, Sensor{i});
		}
	}
}


} // namespace OpKey
