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

	constexpr const auto statusReportDelay = 10000000;
	int64_t lastStatusReportTime = esp_timer_get_time();
	int totalUpdates = 0;

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
						ledStrip[(Sensor::keyCount * 2) - 1] = pixel;
					} else {
						ledStrip[1] = pixel;
					}
				});
				break;
			}

			case Mode::NormalOperation: {
				auto& softPedalState = logicStates[Sensor::softPedal];
				auto& dampPedalState = logicStates[Sensor::dampPedal];

				// TODO as config variable
				constexpr const auto damperPedalPassiveDecayHalfLifeTime = 300000.0;
				constexpr const auto damperPedalPassiveDecayThreshold = 0.2;

				//TODO VisualizeNormal();
				Sensor::ForEachKey([&](Sensor key) {
					size_t ledIndex = (Sensor::keyCount - 1) - key.GetKeyIndex();
					auto& pixel = ledStrip[ledIndex * 2];
					auto& state = logicStates[key];

					if (state.pressed) {
						PixelRgbw targetColor{};
						targetColor.SetHsv(((9.0 - (4.0 * softPedalState.pos)) / 16.0) + (5.0 / 16.0) * state.pressVelocity, 1.0, state.pressVelocity);
						pixel.SetLerp(targetColor, 0.5);
					} else if (dampPedalState.pressed &&
							dampPedalState.lastPressTime < state.lastReleaseTime) {
						auto timeSinceKeyrelease = now - state.lastReleaseTime;
						double decay = (1.0 + damperPedalPassiveDecayThreshold) *
							(damperPedalPassiveDecayHalfLifeTime / (damperPedalPassiveDecayHalfLifeTime + timeSinceKeyrelease))
							- damperPedalPassiveDecayThreshold;
						if (decay < 0.0) {
							decay = 0.0;
						}
						// TODO currently this allows to brighten again when pedal is pressed again.
						// better make a persistent decayed state, which tracks global decay
						// TODO also only calculate press color once, else soft pedal can switch colors
						// live...
						if (dampPedalState.pos < 0.6) {
							decay *= dampPedalState.pos / 0.6;
						}

						PixelRgbw targetColor{};
						targetColor.SetHsv(((9.0 - (4.0 * softPedalState.pos)) / 16.0) + (5.0 / 16.0) * state.pressVelocity, 1.0, decay * state.pressVelocity);
						pixel.SetLerp(targetColor, 0.5);
					} else {
						PixelRgbw targetColor{};
						pixel.SetLerp(targetColor, 0.1);
					}

					//if (state.pressed) {
					//	PixelOn(pixel, state);
					//} else if (dampPedalState.lastPressTime < state.lastPressTime &&
					//		state.lastPressTime < dampPedalState.lastReleaseTime) {
					//	if (dampPedalState.pressed) {
					//		PixelOn(pixel, state);
					//	} else if (deltaDampRelease < 200000) {
					//		PixelLerp(pixel, state, 1.0 - deltaDampRelease / 200000.0);
					//	} else {
					//		pixel.Clear();
					//	}
					//} else if (deltaLastRelease < 200000) {
					//	PixelLerp(pixel, state, 1.0 - deltaLastRelease / 200000.0);
					//} else {
					//	pixel.Clear();
					//}
				});

				//auto sample = Sensor{0x3f};
					//auto& state = logicStates[sample];
					//	auto ledPosition = double(ledIndex) / Sensor::keyCount;
					//	if (ledPosition < state.pressVelocity) {
					//		pixel.SetHsv(ledPosition, 1.0, 0.05);
					//	}

				//// Pedals use the ambient "unused" LEDs in-between keys
				//// TODO
				//PixelRgbw pedalLed{};
				//if (softPedal < .1) { softPedal = 0; }
				//if (dampPedal < .1) { dampPedal = 0; }
				//pedalLed.SetRgb(softPedal * .1, 0.0, dampPedal * .02);
				//for (int i = 0; i < Sensor::keyCount - 1; ++i) {
				//	ledStrip[1 + i * 2] = pedalLed;
				//}
				break;
			}

			default:
				break;
		}

		ledStrip.Update();
		// } while (false);

		lastMode = curMode;

		auto updateBeginTime = now;
		now = esp_timer_get_time();

		auto updateElapsed = now - updateBeginTime;
		auto remainingTimeToWait = config::targetUpdateTimeUs - updateElapsed;
		++totalUpdates;

		taskYIELD();
		if (remainingTimeToWait < 0) {
			// Could not keep up with target fps
			//esp::logw("Could not keep up with target fps!");
		} else if (remainingTimeToWait > 1000) {
			vTaskDelay((remainingTimeToWait + 500) / (1000 * portTICK_PERIOD_MS));
		}

		auto deltaLastStatusReport = now - lastStatusReportTime;
		if (deltaLastStatusReport > statusReportDelay) {
			esp::logi("visualizer: {:5.1f} / {:5.1f} fps (actual/target)"
				, totalUpdates * 1000000.0 / deltaLastStatusReport
				, config::targetFps
				);
			lastStatusReportTime = esp_timer_get_time();
			totalUpdates = 0;
		}
	}
}

void Visualizer::OnTick() {
	OPKEY_PROFILE_FUNCTION();
	logicStates = sensorManager.GetLogicStates();
}

void Visualizer::OnModeChange(Mode /*oldMode*/, Mode /*newMode*/) {
}

// TODO only OnSensorStateChangeFrameComplete
void Visualizer::OnSensorStateChange(const SensorManager& sensorManager, Sensor sensor) {
	if (sensor.IsPedal()) {
		return;
	}

	//auto& h0 = sensorManager.GetHistory()[0];
	//auto& state = h0.state[sensor];

	////std::scoped_lock lock{spinlock};

	//size_t ledIndex = (Sensor::keyCount - 1) - sensor.GetKeyIndex();
	//if (state.pressed) {
	//	ledStrip[ledIndex] = { 0, 20, 30, 10 };
	//} else {
	//	// TODO ledStrip[ledIndex] = { };
	//}

	//TODO needsUpdate = true;
}


} // namespace opkey
