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

	constexpr auto releaseThresholdPosFactor = 0.3;
	/**
	 * Maximum time in microseconds between max velocity and trigger events
	 * which still causes a trigger
	 */
	constexpr auto maxTriggerTimeUs = 40000;

	constexpr auto thresholdTriggerVelocity = 1.0;
	constexpr auto triggerThresholdPosEmaDiff = 0.2;
	constexpr auto triggerThresholdVel = 3.0;
	/** alpha factor for exponential moving average of pos. */
	constexpr auto posEmaAlpha = 0.1;
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
	state.posEma = state.posEma * (1.0 - posEmaAlpha) + state.pos * posEmaAlpha;
	state.velEma = state.velEma * (1.0 - velEmaAlpha) + state.vel * velEmaAlpha;

	state.changed = false;
	if (state.pressed) {
		if (state.maxVelPos - state.pos > releaseThresholdPosFactor * state.maxVelPos) {
			// The key was pressed and since then it has travelled up for
			// more than releaseThresholdPosFactor (percentage) of the hit position.
			state.pressed = false;
			state.changed = true;
			state.lastReleaseTime = now;

			// Reset trigger variables
			state.maxVel = 0.0;
			state.maxVelTime = 0;
			state.maxVelPos = 0.0;
			state.maxVelPosEma = 0.0;
			state.maxVelEma = 0.0;
		}
	} else {
		// If the velocity is greater than the current max velocity
		if (state.vel > state.maxVel) {
			// Check for a viable velocity maximum
			if (state.vel >= 10 || (state.pos > .25 && state.vel > 3)) {
				state.maxVel = state.vel;
				state.maxVelTime = now;
				state.maxVelPos = state.pos;
				state.maxVelPosEma = state.posEma;
				state.maxVelEma = state.velEma;
			}
		}

		// Check falling edge on velocity over thresholdTriggerVelocity
		if (prevVel > thresholdTriggerVelocity && state.vel <= thresholdTriggerVelocity) {
			// Check if the trigger is still valid, and prevent triggers
			// from key-release jittering
			if (now - state.maxVelTime <= maxTriggerTimeUs && now - state.lastReleaseTime > 15000) {
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
				state.maxVel = 0.0;
				state.maxVelTime = 0;
				state.maxVelPos = 0.0;
				state.maxVelPosEma = 0.0;
				state.maxVelEma = 0.0;
			}
		}
	}


	//state.changed = false;
	//if (state.pressed) {
	//	if ((state.maxPos - state.pos) > keyReleaseTravel) {
	//		// The key was pressed and the position has travelled
	//		// backwards enough to consider the key released.
	//		state.pressed = false;
	//		state.changed = true;
	//		state.lastReleaseTime = now;

	//		state.lastAdjust = now;
	//		state.minPos = state.pos;
	//		state.minTime = now;
	//		state.maxPos = state.pos;
	//		state.maxTime = now;
	//	}
	//} else {

	//state.changed = false;
	//if (state.pressed) {
	//	if ((state.maxPos - state.pos) > keyReleaseTravel) {
	//		// The key was pressed and the position has travelled
	//		// backwards enough to consider the key released.
	//		state.pressed = false;
	//		state.changed = true;
	//		state.lastReleaseTime = now;

	//		state.lastAdjust = now;
	//		state.minPos = state.pos;
	//		state.minTime = now;
	//		state.maxPos = state.pos;
	//		state.maxTime = now;
	//	}
	//} else {
	//	if (state.pos < state.minPos) {
	//		state.lastAdjust = now;
	//		state.minPos = state.pos;
	//		state.minTime = now;
	//		state.maxPos = state.pos;
	//		state.maxTime = now;
	//	} else if (state.pos > state.maxPos) {
	//		state.maxPos = state.pos;
	//		state.maxTime = now;
	//	}

	//	auto Trigger = [&] {
	//		// The position is past the high threshold
	//		auto risingEdgeDeltaTime = state.maxTime - state.minTime;
	//		state.pressed = true;
	//		state.changed = true;
	//		state.lastPressTime = state.maxTime;

	//		// TODO apply velocity curve config::VelocityCurve(...)
	//		state.pressVelocity = (state.maxPos - state.minPos) * 1000000.0 / risingEdgeDeltaTime;
	//		auto TODO_RAW_PRESS_VELO = state.pressVelocity;

	//		if (state.pressVelocity < 20.0) {
	//			state.pressVelocity /= 26.0;
	//		} else {
	//			// Compress
	//			state.pressVelocity = 20.0 / 26.0 + (state.pressVelocity - 20.0) / 50.0;
	//		}

	//		if (state.pressVelocity > 1.0) {
	//			state.pressVelocity = 1.0;
	//		}

	//		fmt::print("avgtime {:8.3f}us, key[0x{:02x}, {:4s}] down [min,max]: [{:7.2f},{:7.2f}@{:6d}] vel: {:7.2f}\n",
	//				state.avgTimeStep,
	//				sensor.GetIndex(),
	//				sensor.GetName(),
	//				state.minPos,
	//				state.maxPos,
	//				risingEdgeDeltaTime,
	//				TODO_RAW_PRESS_VELO);
	//	};

	//	// TODO 0.1 pos in 100,000us
	//	// TODO if pos change < X after 10 ms,
	//	// reset min to cur
	//	if ((now - state.lastAdjust) > 10000) {
	//		if (state.pos - state.minPos < 0.01) {
	//			if (state.maxPos - state.minPos > .2) {
	//				if (state.maxTime - state.minTime > 40000) {
	//					Trigger();
	//				}
	//			} else {
	//				state.lastAdjust = now;
	//				state.minPos = state.pos;
	//				state.minTime = now;
	//				state.maxPos = state.pos;
	//				state.maxTime = now;
	//			}
	//		}
	//	}

	//	// TODO at least 40 ms attack time
	//	if (state.maxTime - state.minTime > 40000) {
	//		// TODO at least 20% travel for a keystroke
	//		if (state.maxPos - state.minPos > .2) {
	//			if ((state.maxPos - state.pos) > .15) {
	//				Trigger();
	//			}
	//		}
	//	}

	//	// TODO tendency calculation?
	//	// TODO PLOT THIS SHIT
	//	//tendency = tendency * .8 + velocity * .2;
	//}


	// TODO
	// if pressed
	//	 if (lastHigh - pos) > keyEesetTravel
	//	   lastReleaseTime = ...
	// else
	//   if (pos < min)
	//     min = pos
	//     minTime = now
	//   else if (pos > max)
	//     max = newmax
	//     maxTime = now
	//
	//   if wasGoingDown && lastpos < pos
	//     local minimum
	//     -> reset min time
	//     if (lastMinPos - curMinPos / time  -->  velocity over that time smaller than X)
	//	      min = pos
	//	      minTime = now
	//   else if not wasGoingDown && lastpos > pos
	//     local maximum
	//     -> reset max time
	//
	//   if max - min > minKeyTravelForPress
	//     if max - pos < keyBacktravelToTrigger
	//       if maxtime-mintime > minAttackTime
	//         trigger now

	//// TODO maximum press time?
	//// TODO check attack slopes at thresholds to calc hit velocity?
	//state.changed = false;
	//if (state.pressed) {
	//	if (state.pos < config::posLowThreshold) {
	//		// The key was pressed and the position is now
	//		// below the low threshold, so it is now released
	//		state.pressed = false;
	//		state.changed = true;
	//		state.lastReleaseTime = now;

	//		// 0 is not used for an invalid state here, but rather to ensure
	//		// that all calculations with it will yield a high difference to 'now'.
	//		state.lowRisingEdgeTime = 0;
	//		state.controlRisingEdgeTime = 0;
	//	}
	//} else {
	//	// TODO state system? else ifs are carrying some intermediate states

	//	// TODO maybe choose a backupControlThreshold, that is ALWAYS hit by any sufficient keypress.
	//	// if then the high or low thresholds are not met, and if we record local minima and maxima
	//	// between, then we can calculate a keypress even if it missed the low/high threshold

	//	if (prevPos < config::posLowThreshold &&
	//			state.pos >= config::posLowThreshold &&
	//			now - state.lowRisingEdgeTime > config::posThresholdJitterDelayUs) {
	//		// The position is the first past the low threshold
	//		state.lowRisingEdgeTime = now;
	//		state.lowRisingEdgePos = state.pos;
	//	} else if (state.pos >= config::posControlThreshold &&
	//			now - state.controlRisingEdgeTime > config::posThresholdJitterDelayUs) {
	//		// The position is at or past the control threshold
	//		state.controlRisingEdgeTime = now;
	//		state.controlRisingEdgePos = state.pos;
	//	} else if (state.pos >= config::posHighThreshold) {
	//		// The position is past the high threshold
	//		auto risingEdgeDeltaTime = now - state.lowRisingEdgeTime;
	//		state.pressed = true;
	//		state.changed = true;
	//		state.lastPressTime = now;

	//		// TODO apply velocity curve config::VelocityCurve(...)
	//		state.pressVelocity = (state.pos - state.lowRisingEdgePos) * 1000000.0 / risingEdgeDeltaTime;
	//		auto TODO_RAW_PRESS_VELO = state.pressVelocity;

	//		if (state.pressVelocity < 20.0) {
	//			state.pressVelocity /= 26.0;
	//		} else {
	//			// Compress
	//			state.pressVelocity = 20.0 / 26.0 + (state.pressVelocity - 20.0) / 50.0;
	//		}

	//		if (state.pressVelocity > 1.0) {
	//			state.pressVelocity = 1.0;
	//		}

	//		fmt::print("avgtime {:8.3f}us, key[0x{:02x}, {:4s}] down [l,c,h]: [{:7.2f},{:7.2f}@{:6d},{:7.2f}@{:6d}] vel: {:7.2f}\n",
	//				state.avgTimeStep,
	//				sensor.GetIndex(),
	//				sensor.GetName(),
	//				state.lowRisingEdgePos,
	//				state.controlRisingEdgePos,
	//				state.controlRisingEdgeTime - state.lowRisingEdgeTime,
	//				state.pos,
	//				now - state.lowRisingEdgeTime,
	//				TODO_RAW_PRESS_VELO);
	//	}
	//}
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
