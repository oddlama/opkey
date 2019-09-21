#include "calibration.h"
#include "config.h"
#include "visualizer.h"
#include "application.h"
#include "sensor_manager.h"


namespace opkey {


Visualizer::Visualizer(Application& application)
	: onTickConnection(application.GetOnTickSink().connect<&Visualizer::OnTick>(*this))
	, onModeChangeConnection(application.GetOnModeChangeSink().connect<&Visualizer::OnModeChange>(*this))
	, onSensorStateChangeConnection(application.GetOnSensorStateChangeSink().connect<&Visualizer::OnSensorStateChange>(*this))
	, sensorManager(application.GetSensorManager())
{
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
	Mode lastMode = Mode::Idle;
	while (true) {
		//do {
			//std::scoped_lock lock{spinlock};

			//if (not needsUpdate) {
			//	break;
			//}
			//needsUpdate = false;

		auto now = esp_timer_get_time();

		auto curMode = Application::instance->GetMode();
		if (curMode != lastMode) {
			ledStrip.Clear();
		}

		switch (curMode) {
			case Mode::Calibrate: {
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

				Sensor::ForEachPedal([&](Sensor pedal) {
					PixelRgbw pixel{};
					const auto& c = calibration::calibrationData[pedal];

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

					// TODO temporary......
					//// The 0.9 offset (<1.0) is to counter any potential rounding errors.
					//double ledsPerPedal = 0.9 + static_cast<double>(Sensor::keyCount - 1) / Sensor::pedalCount;
					//int from = static_cast<int>((pedal.GetPedalIndex()) * ledsPerPedal);
					//int to = static_cast<int>((pedal.GetPedalIndex() + 1) * ledsPerPedal);
					//for (int i = from; i < to; ++i) {
					//	ledStrip[1 + i * 2] = pixel;
					//}

					if (pedal.GetPedalIndex() == 0) {
						ledStrip[(Sensor::keyCount * 2) - 2] = pixel;
					} else {
						ledStrip[1] = pixel;
					}
				});
				break;
			}

			case Mode::NormalOperation: {
				//TODO VisualizeNormal();
				Sensor::ForEachKey([&](Sensor key) {
					size_t ledIndex = (Sensor::keyCount - 1) - key.GetKeyIndex();
					auto& pixel = ledStrip[ledIndex * 2];
					auto& logicState = logicStates[key];

					auto deltaLastRelease = now - logicState.lastReleaseTime;
					if (logicState.pressed) {
						pixel.SetHsv(1/8. + logicState.pressVelocity * 5/8., 1.0, logicState.pressVelocity);
					} else if (deltaLastRelease > 200000) {
						pixel.Clear();
					} else {
						double df = 1.0 - (deltaLastRelease / 200000.0);
						pixel.SetHsv(1/8. + logicState.pressVelocity * 5/8., 1.0, df * logicState.pressVelocity);
					}
				});

				// Pedals use the in-between leds
				PixelRgbw pedalLed{};
				double softPedal = logicStates[Sensor::pedalOffset + 0].pos;
				if (softPedal < .1) { softPedal = 0; }
				double dampPedal = logicStates[Sensor::pedalOffset + 1].pos;
				if (dampPedal < .1) { dampPedal = 0; }
				pedalLed.SetRgb(softPedal * .1, 0.0, dampPedal * .1);
				for (int i = 0; i < Sensor::keyCount - 1; ++i) {
					ledStrip[1 + i * 2] = pedalLed;
				}
				break;
			}

			default:
				break;
		}

		ledStrip.Update();
#ifndef NDEBUG
		++debugLedFpsCount;
#endif
		// } while (false);

		lastMode = curMode;
		taskYIELD();
		// TODO wait only what is remaining X - now + begin to get X fps, with X being a config variable for vis fps
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}

void Visualizer::OnTick() {
	OPKEY_PROFILE_FUNCTION();
	logicStates = sensorManager.GetLogicStates();

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

void Visualizer::OnModeChange(Mode /*oldMode*/, Mode /*newMode*/) {
}

// TODO only OnSensorStateChangeFrameComplete
void Visualizer::OnSensorStateChange(const SensorManager& sensorManager, Sensor sensor) {
	if (sensor.IsPedal()) {
		return;
	}

	//auto& h0 = sensorManager.GetHistory()[0];
	//auto& logicState = h0.logicState[sensor];

	////std::scoped_lock lock{spinlock};

	//size_t ledIndex = (Sensor::keyCount - 1) - sensor.GetKeyIndex();
	//if (logicState.pressed) {
	//	ledStrip[ledIndex] = { 0, 20, 30, 10 };
	//} else {
	//	// TODO ledStrip[ledIndex] = { };
	//}

	//TODO needsUpdate = true;
}


} // namespace opkey
