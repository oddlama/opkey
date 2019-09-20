#include "sensor_manager.h"
#include "calibration.h"
#include "application.h"

#include <driver/uart.h>


namespace opkey {


static SensorData tmpData{};


SensorManager::SensorManager(Application& application)
	: onTickConnection(application.GetOnTickSink().connect<&SensorManager::OnTick>(*this))
	, onModeChangeConnection(application.GetOnModeChangeSink().connect<&SensorManager::OnModeChange>(*this))
{ }


/**
 * Initialize the states with the given valid data
 */
void SensorManager::InitLogicStates(SensorData& newData) {
	OPKEY_PROFILE_FUNCTION();

	// Clean initial state
	logicStates = {};
	CalculateNextSensorState(newData);
}

void SensorManager::InitSingleSensorHistory() {
	singleSensorHistory = {};
}

void SensorManager::CalculateNextSensorState(SensorData& newData) {
	OPKEY_PROFILE_FUNCTION();

	auto now = esp_timer_get_time();

	for (size_t i = 0; i < newData.size(); ++i) {
		auto& state = logicStates[i];

		// 1. Swizzle the raw data to match the sensor order
		// 2. Position is sqrt(data), because light intensity is 1/(distance^2)
		auto rawPos = sqrt(newData[config::GetSensorSwizzle(i)]);
		// 3. Apply calibration
		auto prevPos = state.pos;
		state.pos = calibration::calibrationData[i].Apply(rawPos);

		// TODO maximum press time?
		// TODO check attack slopes at thresholds to calc hit velocity?
		state.changed = false;
		if (state.pressed) {
			if (state.pos < config::posLowThreshold) {
				// The key was pressed and the position is now
				// below the low threshold, so it is now released
				state.pressed = false;
				state.changed = true;
				state.lastReleaseTime = now;

				// 0 is not used for an invalid state here, but rather to ensure
				// that all calculations with it will yield a high difference to 'now'.
				state.lowRisingEdgeTime = 0;
				state.controlRisingEdgeTime = 0;
			}
		} else {
			// TODO state system? else ifs are carrying some intermediate states

			// TODO maybe choose a backupControlThreshold, that is ALWAYS hit by any sufficient keypress.
			// if then the high or low thresholds are not met, and if we record local minima and maxima
			// between, then we can calculate a keypress even if it missed the low/high threshold

			// Key was is pressed
			if (prevPos < config::posLowThreshold &&
					state.pos >= config::posLowThreshold &&
					now - state.lowRisingEdgeTime > config::posThresholdJitterDelayUs) {
				// The position is the first past the low threshold
				state.lowRisingEdgeTime = now;
				state.lowRisingEdgePos = state.pos;
			} else if (state.pos >= config::posControlThreshold &&
					now - state.controlRisingEdgeTime > config::posThresholdJitterDelayUs) {
				// The position is at or past the control threshold
				state.controlRisingEdgeTime = now;
				state.controlRisingEdgePos = state.pos;
			} else if (state.pos >= config::posHighThreshold) {
				// The position is past the high threshold
				auto risingEdgeDeltaTime = now - state.lowRisingEdgeTime;
				state.pressed = true;
				state.changed = true;
				state.lastPressTime = now;

				// TODO apply velocity curve config::VelocityCurve(...)
				state.pressVelocity = (state.pos - state.lowRisingEdgePos) * 1000000.0 / risingEdgeDeltaTime;
				auto TODO_RAW_PRESS_VELO = state.pressVelocity;

				if (state.pressVelocity < 20.0) {
					state.pressVelocity /= 26.0;
				} else {
					// Compress
					state.pressVelocity = 20.0 / 26.0 + (state.pressVelocity - 20.0) / 50.0;
				}

				if (state.pressVelocity > 1.0) {
					state.pressVelocity = 1.0;
				}

				fmt::print("key[0x{:02x}, {:4s}] down [l,c,h]: [{:7.2f},{:7.2f}@{:6d},{:7.2f}@{:6d}] vel: {:7.2f}\n",
						Sensor{i}.GetIndex(),
						Sensor{i}.GetName(),
						state.lowRisingEdgePos,
						state.controlRisingEdgePos,
						state.controlRisingEdgeTime - state.lowRisingEdgeTime,
						state.pos,
						now - state.lowRisingEdgeTime,
						TODO_RAW_PRESS_VELO);
			}
		}
	}
}


void SensorManager::OnTick() {
	OPKEY_PROFILE_FUNCTION();

	switch (Application::instance->GetMode()) {
		case Mode::Calibrate: {
			// TODO settings for samples
			adcController.Read(tmpData, 2);
			if (calibration::Calibrate(tmpData)) {
				// Calibration is finished
				calibration::Save();
				Application::instance->SetNextMode(Mode::NormalOperation);
			}
			break;
		}

		case Mode::SingleSensorMonitoring: {
			// TODO debug disable bt: nimble_port_stop();
			// TODO debug disable bt: nimble_port_deinit();
			// TODO debug disable bt: esp_nimble_hci_and_controller_deinit();
			while (true) {
				// esp32 uart safe data conversion
				auto WriteEnc = [](const auto* data, size_t count) {
					static std::array<uint16_t, 32> sendBuf{};
					static size_t sendBufCount = 0;

					sendBufCount = 0;
					auto begin = reinterpret_cast<const uint8_t*>(data);
					auto end = begin + count;
					for (auto d = begin; d != end; ++d) {
						sendBuf[sendBufCount] =
							((((*d & 0x0f) >> 0) + 'a') << 0) |
							((((*d & 0xf0) >> 4) + 'a') << 8);
						if (++sendBufCount == sendBuf.size()) {
							write(1, sendBuf.data(), sizeof(uint16_t) * sendBuf.size());
							sendBufCount = 0;
						}
					}

					if (sendBufCount > 0) {
						write(1, sendBuf.data(), sizeof(uint16_t) * sendBufCount);
					}
				};

				// Countdown
				fmt::print("3...\n");
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				fmt::print("2...\n");
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				// Notify host of pending capture
				write(1, "\005\005\005\005\005\005\005\005", 8);
				fmt::print("1...\n");
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				fmt::print("NOW!\n");

				// Read data
				auto now = esp_timer_get_time();
				adcController.ReadSingle(singleSensorHistory.data(), singleSensorHistory.size());
				auto fin = esp_timer_get_time();

				// Notify host of finished capture
				write(1, "\004\004\004\004\004\004\004\004", 8);
				auto diff = fin - now;

				// Notify host of beginning transaction
				write(1, "\027\027\027\027\027\027\027\027", 8);

				std::array<char, 4> sensorName{};
				memcpy(sensorName.data(), mode_params::singleSensorMonitoringSensor.GetName(), strlen(mode_params::singleSensorMonitoringSensor.GetName()));
				WriteEnc(sensorName.data(), sensorName.size());

				WriteEnc(&calibration::calibrationData[mode_params::singleSensorMonitoringSensor].min, sizeof(double));
				WriteEnc(&calibration::calibrationData[mode_params::singleSensorMonitoringSensor].max, sizeof(double));
				WriteEnc(&diff, sizeof(diff));
				uint32_t dataPoints = singleSensorHistory.size();
				WriteEnc(&dataPoints, sizeof(dataPoints));
				WriteEnc(&singleSensorHistory, sizeof(singleSensorHistory));
			}
			break;
		}

		case Mode::NormalOperation: {
			// TODO settings for samples
			adcController.Read(tmpData, 2);
			CalculateNextSensorState(tmpData);

			// Notify listeners if a key state has changed
			Sensor::ForEachKey([&](Sensor key) {
				if (logicStates[key].changed) {
					onSensorStateChangeSignal.publish(*this, key);
				}
			});
			break;
		}

		default:
			break;
	}
}

void SensorManager::OnModeChange(Mode oldMode, Mode newMode) {
	switch (newMode) {
		case Mode::Calibrate: {
			adcController.SetAdcModeAuto();
			calibration::Reset();
			break;
		}

		case Mode::LoadConfig:
			calibration::Load();
			break;

		case Mode::SingleSensorMonitoring:
			adcController.SetAdcModeSingle();
			InitSingleSensorHistory();
			break;

		default: {
			adcController.SetAdcModeAuto();
			adcController.Read(tmpData, 512);
			InitLogicStates(tmpData);
			break;
		}
	}
}


} // namespace opkey
