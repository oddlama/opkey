#include "calibration.h"
#include "config.h"
#include "visualizer.h"
#include "application.h"
#include "sensor_manager.h"


namespace opkey {


Visualizer::Visualizer(Application& application)
	: onTickConnection(application.GetOnTickSink().connect<&Visualizer::OnTick>(*this))
	, onSensorStateChangeConnection(application.GetOnSensorStateChangeSink().connect<&Visualizer::OnSensorStateChange>(*this))
	, sensorManager(application.GetSensorManager())
{
	logicStateData = &sensorManager.GetHistory()[0].keyState;
	static auto DispatchMain = [](void* param) [[noreturn]] {
		try {
			static_cast<Visualizer*>(param)->TaskMain();
		} catch(std::exception& e) {
			esp::loge("Caught exception: {}\nAborting.", e.what());
			abort();
		} catch(...) {
			esp::loge("Caught unkown exception type\nAborting.");
			abort();
		}
	};

	xTaskCreatePinnedToCore(DispatchMain, "OpKeyVisualizer", 8192, this, tskIDLE_PRIORITY + 1, &taskHandle, opkey::config::VisualizerCore);
}

Visualizer::~Visualizer() noexcept {
	vTaskDelete(taskHandle);
}


void Visualizer::TaskMain() {
	while (true) {
		//do {
			//std::scoped_lock lock{spinlock};

			//if (not needsUpdate) {
			//	break;
			//}
			//needsUpdate = false;

		auto now = esp_timer_get_time();

		switch (Application::instance->GetMode()) {
			case Mode::Calibrate:
				//TODO VisualizeCalibration();
				Sensor::ForEachKey([&](Sensor key) {
					size_t ledIndex = (Sensor::keyCount - 1) - key.GetKeyIndex();
					auto& pixel = ledStrip[ledIndex * 2];
					const auto& c = calibration::calibrationData[key];

					switch (c.GetCalibrationStatus()) {
						default:
						case calibration::CalibrationStatus::InvalidMinMax:       pixel = {  0, 20,  0, 1 }; break;
						case calibration::CalibrationStatus::MissingFirstUpdate:  pixel = {  0, 20, 20, 1 }; break;
						case calibration::CalibrationStatus::MissingUsage:        pixel = {
							static_cast<uint8_t>(
									20 * (std::min(c.usageCycles, config::requiredCalibrationCycles)
									/ static_cast<double>(config::requiredCalibrationCycles))), 30,  0, 0 }; break;
						case calibration::CalibrationStatus::RangeToSmall:        pixel = {  0, 20, 20, 1 }; break;
						case calibration::CalibrationStatus::Calibrated:          pixel = { 20,  0,  0, 1 }; break;
					}
				});
				break;

			case Mode::NormalOperation:
				//TODO VisualizeNormal();
				Sensor::ForEachKey([&](Sensor key) {
					size_t ledIndex = (Sensor::keyCount - 1) - key.GetKeyIndex();
					auto& pixel = ledStrip[ledIndex * 2];
					auto& keyState = (*logicStateData)[key];

					auto deltaLastRelease = now - keyState.lastReleaseTime;
					if (keyState.pressed) {
						pixel = { 40, 0, 40, 10 };
					} else if (deltaLastRelease > 200000) {
						pixel = { };
					} else {
						double df = 1.0 - (deltaLastRelease / 200000.0);
						pixel =
							{ static_cast<uint8_t>(df * 40)
							, 0
							, static_cast<uint8_t>(df * 40)
							, static_cast<uint8_t>(df * 10)
							};
					}
				});
				break;

			default:
				break;
		}

		ledStrip.Update();
#ifndef NDEBUG
		++debugLedFpsCount;
#endif
		// } while (false);

		taskYIELD();
		// TODO wait only what is remaining X - now + begin to get X fps, with X being a config variable for vis fps
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}

void Visualizer::OnTick() {
	OPKEY_PROFILE_FUNCTION();
	logicStateData = &sensorManager.GetHistory()[0].keyState;

#ifndef NDEBUG
	int64_t now = esp_timer_get_time();
	auto diff = now - debugLedFpsTime;
	if (diff > 1000000) {
		fmt::print("Visualizer fps: {}\n", debugLedFpsCount * 1000000.0 / diff);
		debugLedFpsTime = now;
		debugLedFpsCount = 0;
	}
#endif
}

void Visualizer::OnSensorStateChange(const SensorManager& sensorManager, Sensor sensor) {
	if (sensor.IsPedal()) {
		return;
	}

	//auto& h0 = sensorManager.GetHistory()[0];
	//auto& keyState = h0.keyState[sensor];

	////std::scoped_lock lock{spinlock};

	//size_t ledIndex = (Sensor::keyCount - 1) - sensor.GetKeyIndex();
	//if (keyState.pressed) {
	//	ledStrip[ledIndex] = { 0, 20, 30, 10 };
	//} else {
	//	// TODO ledStrip[ledIndex] = { };
	//}

	needsUpdate = true;
}


} // namespace opkey
