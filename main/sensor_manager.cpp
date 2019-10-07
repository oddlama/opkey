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

	for (size_t i = 0; i < newData.size(); ++i) {
		CalculateNextSensorState(i, newData[i]);
	}
}

void SensorManager::CalculateNextSensorState(size_t rawIndex, double newData) {
	OPKEY_PROFILE_FUNCTION();

	auto sensor = Sensor{config::GetSensorIndexFromRawIndex(rawIndex)};
	auto& state = logicStates[sensor];

	auto now = esp_timer_get_time();
	auto deltaTime = now - state.lastUpdateTime;
	state.lastUpdateTime = now;

	/** Alpha factor for exponential moving average of vel. */
	constexpr auto velEmaAlpha = 0.1;

	// Store previous values
	auto prevPos = state.pos;
	auto prevVel = state.vel;

	// 1. Position is sqrt(data), because light intensity is 1/(distance^2)
	// 2. Apply calibration
	auto rawPos = sqrt(newData);
	state.pos = calibration::calibrationData[sensor].Apply(rawPos);
	state.vel = (state.pos - prevPos) * (1000000.0 / deltaTime);

	// Calculate exponetial moving average (EMA) of pos and vel
	state.velEma = state.velEma * (1.0 - velEmaAlpha) + state.vel * velEmaAlpha;

	state.changed = false;
	if (state.pressed) {
		if (state.maxVelPos - state.pos > config::releasePositionThreshold * state.maxVelPos) {
			// The key was pressed and since then it has travelled up for
			// more than config::releasePositionThreshold (percentage) of the hit position.
			state.pressed = false;
			state.changed = true;
			state.lastReleaseTime = now;

			// Reset trigger variables
			state.maxVelTime = 0;
			state.maxVel = 0.0;
			state.maxVelEma = 0.0;
			state.maxVelPos = 0.0;
		}
	} else {
		// If the velocity is greater than the current max velocity
		if (state.vel > state.maxVel) {
			// Check for a valid velocity maximum
			if (config::IsValidVelocityMaximum(state.pos, state.vel)) {
				state.maxVelTime = now;
				state.maxVel = state.vel;
				state.maxVelEma = state.velEma;
				state.maxVelPos = state.pos;
			}
		}

		// Check falling edge on velocity over config::triggerVelocityThreshold
		if (prevVel > config::triggerVelocityThreshold &&
				state.vel <= config::triggerVelocityThreshold) {
			// Check if the trigger is still valid, and prevent triggers
			// from key-release jittering
			if (now - state.maxVelTime <= config::maxTriggerDelayUs &&
					now - state.lastReleaseTime > config::minTriggerJitterDelayUs) {
				// The position is past the high threshold
				state.pressed = true;
				state.changed = true;
				state.lastPressTime = state.maxVelTime;

				// TODO apply velocity curve config::VelocityCurve(...)
				state.pressVelocity = state.maxVel - state.maxVelEma;
				if (state.pressVelocity < 0.0) {
					state.pressVelocity = 0.0;
				} else if (state.pressVelocity < 40.0) {
					// Linear for low and medium velocities
					state.pressVelocity /= 50.0;
				} else if (state.pressVelocity < 80.0) {
					// Compress high velocities
					state.pressVelocity = 0.8 + (state.pressVelocity - 40.0) / 40.0 * 0.2;
				} else {
					state.pressVelocity = 1.0;
				}
				//state.pressVelocity = std::clamp(state.pressVelocity, 0.0, 1.0);

				//fmt::print("[2;37mkey[0x{:02x}, {:4s}] possible: pos {:7.2f} vel {:7.2f} EMApd{:7.2f} EMAvd {:7.2f}[m\n",
				//	sensor.GetIndex(),
				//	sensor.GetName(),
				//	state.pos,
				//	state.vel,
				//	state.maxVelPosEma - state.maxVelPos,
				//	state.maxVelEma - state.maxVel
				//	);
				//fmt::print("key[0x{:02x}, {:4s}] down: vel: {:7.2f}\n",
				//	sensor.GetIndex(),
				//	sensor.GetName(),
				//	state.pressVelocity);
			} else {
				// The trigger has expired, reset max velocity state
				state.maxVelTime = 0;
				state.maxVel = 0.0;
				state.maxVelEma = 0.0;
				state.maxVelPos = 0.0;
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
				adcController.ReadSingle(singleSensorHistory.data(), singleSensorHistory.size(), 1800);
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
			adcController.Read([&](auto rawIndex, auto data) {
					CalculateNextSensorState(rawIndex, data);
				});

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
