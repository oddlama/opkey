#include "sensor_manager.h"
#include "application.h"


namespace OpKey {


SensorManager::SensorManager(Application& application)
	: onTickConnection(application.GetOnTickSink().connect<&SensorManager::OnTick>(*this))
{ }


void SensorManager::OnTick() {
	OPKEY_PROFILE_FUNCTION();
	//RawSensorData d;
	SensorTensor<double> data{};
	//adcController.Read(data);
	adcController.Read(data, 8);
	//history.
	//adcController.Read(buffer, Settings::GetMultisamples());
}


} // namespace OpKey
