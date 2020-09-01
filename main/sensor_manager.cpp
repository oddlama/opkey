#include "sensor_manager.h"
#include "calibration.h"
#include "application.h"

#include <driver/uart.h>


namespace opkey {

#ifdef ENABLE_SINGLE_SENSOR_MONITORING
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
#endif

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
#ifdef ENABLE_SINGLE_SENSOR_MONITORING
	singleSensorHistory = {};
#endif
}

void SensorManager::CalculateNextSensorState(SensorData& newData) {
	OPKEY_PROFILE_FUNCTION();

	for (size_t i = 0; i < newData.size(); ++i) {
		CalculateNextSensorState(i, newData[i]);
	}
}

void SensorManager::CalculateNextSensorState(size_t rawIndex, double newData) {
	OPKEY_PROFILE_FUNCTION();

	// TODO static int64_t lastu = 0;
	// TODO static int xki = 0;
	// TODO if (rawIndex == 0) {
	// TODO 	++xki;
	// TODO 	auto now = esp_timer_get_time();
	// TODO 	auto diff = now - lastu;
	// TODO 	if (diff > 1000000) {
	// TODO 		fmt::print("tickrate per key: every {} us = {} tps\n", diff / xki, 1000000.0 * xki / diff);
	// TODO 		xki = 0;
	// TODO 		lastu = now;
	// TODO 	}
	// TODO }
	auto sensor = Sensor{config::GetSensorIndexFromRawIndex(rawIndex)};
	auto& state = logicStates[sensor];

	auto now = esp_timer_get_time();
	auto deltaTime = now - state.lastUpdateTime;
	state.lastUpdateTime = now;

#ifdef ENABLE_SINGLE_SENSOR_MONITORING
	state.delta = deltaTime;
	state.rawPos = static_cast<uint16_t>(newData * ads7953::values);
#endif

	// Store previous values
	auto prevPos = state.posHistory[state.currentHistoryIndex];
	auto prevVel = state.vel;

	//static int iii = 1;
	//if (iii % 100 == 0) {
	//	if (sensor.GetIndex() == 0x10u+0*12u || sensor.GetIndex() == 0x10u+0*12u+1u ||
	//		sensor.GetIndex() == 0x10u+1*12u || sensor.GetIndex() == 0x10u+1*12u+1u ||
	//		sensor.GetIndex() == 0x10u+2*12u || sensor.GetIndex() == 0x10u+2*12u+1u)
	//	{
	//		fmt::print("key[0x{:02x}, {:4s}] rawpos {}\n",
	//			sensor.GetIndex(),
	//			sensor.GetName(),
	//			newData);
	//	}
	//}
	//if (sensor.GetIndex() == 0u) {
	//	if (++iii == 1001) {
	//		iii = 1;
	//	}
	//}
	//// 1. Position is sqrt(data), because light intensity is 1/(distance^2)
	//// 2. Apply calibration
	//auto rawPos = sqrt(newData);
	//state.pos = calibration::calibrationData[sensor].Apply(rawPos);

	auto isWhiteKey = [](auto i) {
		switch (i / 12) {
			default:
			case 0:
			case 2:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
				return true;
			case 1:
			case 4:
			case 6:
			case 9:
			case 11:
				return false;
		}
	};

	if (sensor.IsPedal()) {
		// TODO MISSING MEASUREMENT
		state.pos = sqrt(newData);
	} else if (isWhiteKey(sensor.GetKeyIndex())) {
		// White keys
		state.pos = -1.609864 + (19.9053 / 7.83965) * (1 - exp(-7.83965 * newData));
	} else {
		// Black keys
		state.pos = -0.7957951 + (9.450975 / 6.014812) * (1 - exp(-6.014812 * newData));
	}
	state.vel = (state.pos - prevPos) * (1000000.0 / deltaTime);

	// Save pos in history
	if (++state.currentHistoryIndex == state.posHistory.size()) {
		state.currentHistoryIndex = 0;
	}
	state.posHistory[state.currentHistoryIndex] = state.pos;
	state.deltaHistory[state.currentHistoryIndex] = deltaTime;

	if (sensor.IsPedal()) {
		state.changed = false;
		if (state.pressed) {
			if (state.pos < config::pedalReleaseThreshold) {
				state.changed = true;
				state.pressed = false;
				state.lastReleaseTime = now;
			}
		} else {
			if (state.pos >= config::pedalPressThreshold) {
				state.changed = true;
				state.pressed = true;
				state.lastPressTime = now;
			}
		}
	} else {
		state.changed = false;
		if (state.pressed) {
			if (state.pos < config::releasePositionAbsolute ||
					state.maxVelPos - state.pos > config::releasePositionThreshold * state.maxVelPos) {
				// The key was pressed and since then it has travelled up for
				// more than config::releasePositionThreshold (percentage) of the hit position.
				// Or it has fallen below the absolute release position.
				state.pressed = false;
				state.changed = true;
				state.lastReleaseTime = now;

				// Reset trigger variables
				state.maxVelTime = 0;
				state.maxVel = 0.0;
			}
		} else {
			// If the velocity is greater than the current max velocity
			if (state.vel > state.maxVel) {
				// Check for a valid velocity maximum
				if (config::IsValidVelocityMaximum(state.pos, state.vel)) {
					state.maxVelTime = now;
					state.maxVelPos = state.pos;
					state.maxVel = state.vel;

			 		state.pressed = true;
			 		state.changed = true;
			 		state.lastPressTime = state.maxVelTime;
			 		state.pressVelocity = CalculatePressVelocity(sensor, state);
				}
			}

			// // Check falling edge on velocity over config::triggerVelocityThreshold
			// if (prevVel > config::triggerVelocityThreshold &&
			// 		state.vel <= config::triggerVelocityThreshold) {
			// 	// Check if the trigger is still valid, and prevent triggers
			// 	// from key-release jittering
			// 	if (now - state.maxVelTime <= config::maxTriggerDelayUs &&
			// 			now - state.lastReleaseTime > config::minTriggerJitterDelayUs) {
			// 		// The position is past the high threshold
			// 		state.pressed = true;
			// 		state.changed = true;
			// 		state.lastPressTime = state.maxVelTime;
			// 		state.pressVelocity = CalculatePressVelocity(sensor, state);
			// 		//fmt::print("[2;37mkey[0x{:02x}, {:4s}] possible: pos {:7.2f} vel {:7.2f} EMApd{:7.2f} EMAvd {:7.2f}[m\n",
			// 		//	sensor.GetIndex(),
			// 		//	sensor.GetName(),
			// 		//	state.pos,
			// 		//	state.vel,
			// 		//	state.maxVelPosEma - state.maxVelPos,
			// 		//	state.maxVelEma - state.maxVel
			// 		//	);
			// 		//fmt::print("key[0x{:02x}, {:4s}] down: vel: {:7.2f}\n",
			// 		//	sensor.GetIndex(),
			// 		//	sensor.GetName(),
			// 		//	state.pressVelocity);
			// 	} else {
			// 		// The trigger has expired, reset max velocity state
			// 		state.maxVelTime = 0;
			// 		state.maxVel = 0.0;
			// 	}
			// }
		}
	}
}

double SensorManager::CalculatePressVelocity(Sensor sensor, const LogicState& state) {
	double velMax = 0.0;
	double posAtVelMax = 0.0;

	auto from = state.currentHistoryIndex + 1;
	auto to = from + state.posHistory.size();
	int maxIdx = 0;

	auto lastPos = state.posHistory[from % state.posHistory.size()];
	// Iterate oldest+1 to newest
	double vel_acc_avg = 0.0;
	int vel_acc_avg_cnt = 0;
	for (int i = from + 1; i < to; ++i) {
		auto pos = state.posHistory[i % state.posHistory.size()];
		auto t = state.deltaHistory[i % state.deltaHistory.size()];
		double vel = (pos - lastPos) * (1000000.0 / t);
		//fmt::print("pos {} in {}us; vel {}\n", pos, t, vel);
		if (vel > velMax) {
			vel_acc_avg += vel;
			++vel_acc_avg_cnt;
			velMax = vel;
			maxIdx = i;
			posAtVelMax = pos;
		}
		lastPos = pos;
	}

	vel_acc_avg /= vel_acc_avg_cnt;
	vel_acc_avg -= 3.0;

	//fmt::print("key[0x{:02x}, {:4s}] >>> vaa {:7.2f} <<< pos {:7.2f} velMax {:7.2f}\n",
	//	sensor.GetIndex(),
	//	sensor.GetName(),
	//	vel_acc_avg,
	//	posAtVelMax,
	//	velMax / 50.0);

	return std::clamp(vel_acc_avg / 17.0, 0.0, 1.0);

	//auto x = std::array{ velMax / 60.0, posAtVelMax };

	//// -------- BEGIN GENERATED KERAS MODEL EVALUATION --------
	//static constexpr const std::array<std::array<double, 1>, 2> dense0_weights = {
	//	{ { -2.6731438636779785156250000 }
	//	, {  2.5020406246185302734375000 }
	//	}};
	//static constexpr const std::array<double, 1> dense0_biases =
	//	{  0.2287315726280212402343750 };
	//static constexpr const std::array<std::array<double, 1>, 1> dense1_weights = {
	//	{ { -2.8131725788116455078125000 }
	//	}};
	//static constexpr const std::array<double, 1> dense1_biases =
	//	{ -0.6620918512344360351562500 };
	//double mul0_0x0 =
	//	x[ 0] * dense0_weights[ 0][ 0] +
	//	x[ 1] * dense0_weights[ 1][ 0];
	//double add0_0 = mul0_0x0 + dense0_biases[ 0];
	//double relu0_0 = add0_0 < 0.0 ? 0.0 : add0_0;
	//double mul1_0x0 =
	//	relu0_0 * dense1_weights[ 0][ 0];
	//double add1_0 = mul1_0x0 + dense1_biases[ 0];
	//double tanh1_0 = tanh(add1_0);
	//double y_0 = (tanh1_0 + 1.0) / 2.0;
	//// -------- END GENERATED KERAS MODEL EVALUATION --------

	//y_0 *= 2.3607011588069176;
	//y_0 = std::clamp(y_0, 0.0, 1.0);
	//return y_0;
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
#ifdef ENABLE_SINGLE_SENSOR_MONITORING
			adcController.Read([&](auto rawIndex, auto data) {
					CalculateNextSensorState(rawIndex, data);
				});

			static int slot = 0;
			//constexpr const auto sensorRepetitions = 2;
			//static int repetition = 0;

			singleSensorHistory[slot * 2 + 0] = logicStates[mode_params::singleSensorMonitoringSensor].delta;
			singleSensorHistory[slot * 2 + 1] = logicStates[mode_params::singleSensorMonitoringSensor].rawPos;

			if (++slot == config::singleSensorHistorySize / 2) {
				// Notify host of beginning transaction
				write(1, "\027\027\027\027\027\027\027\027", 8);
				uint32_t dataPoints = singleSensorHistory.size() / 2;
				WriteEnc(&dataPoints, sizeof(dataPoints));
				WriteEnc(&singleSensorHistory, sizeof(singleSensorHistory));
				slot = 0;

				fflush(stdin);
				fflush(stdout);

				//if (++repetition == sensorRepetitions) {
				//	repetition = 0;
				//	size_t s = mode_params::singleSensorMonitoringSensor.GetIndex() + 1;
				//	if (s >= Sensor::keyCount) {
				//		s = Sensor::keyOffset;
				//	}
				//	mode_params::singleSensorMonitoringSensor = Sensor{s};
				//}

				auto now = esp_timer_get_time();
				fmt::print("recording {} in 1 sec...\n", mode_params::singleSensorMonitoringSensor.GetName());
				write(1, "\005\005\005\005\005\005\005\005", 8);
				while (esp_timer_get_time() - now < 1000000) {
					; // wait
				}
				fmt::print("recording\n");
			}

			// TODO debug disable bt: nimble_port_stop();
			// TODO debug disable bt: nimble_port_deinit();
			// TODO debug disable bt: esp_nimble_hci_and_controller_deinit();
			//while (true) {
				// esp32 uart safe data conversion
				//auto WriteEnc = [](const auto* data, size_t count) {
				//	static std::array<uint16_t, 32> sendBuf{};
				//	static size_t sendBufCount = 0;

				//	sendBufCount = 0;
				//	auto begin = reinterpret_cast<const uint8_t*>(data);
				//	auto end = begin + count;
				//	for (auto d = begin; d != end; ++d) {
				//		sendBuf[sendBufCount] =
				//			((((*d & 0x0f) >> 0) + 'a') << 0) |
				//			((((*d & 0xf0) >> 4) + 'a') << 8);
				//		if (++sendBufCount == sendBuf.size()) {
				//			write(1, sendBuf.data(), sizeof(uint16_t) * sendBuf.size());
				//			sendBufCount = 0;
				//		}
				//	}

				//	if (sendBufCount > 0) {
				//		write(1, sendBuf.data(), sizeof(uint16_t) * sendBufCount);
				//	}
				//};

				//// Countdown
				//fmt::print("3...\n");
				//vTaskDelay(1000 / portTICK_PERIOD_MS);
				//fmt::print("2...\n");
				//vTaskDelay(1000 / portTICK_PERIOD_MS);
				//// Notify host of pending capture
				//write(1, "\005\005\005\005\005\005\005\005", 8);
				//fmt::print("1...\n");
				//vTaskDelay(1000 / portTICK_PERIOD_MS);
				//fmt::print("NOW!\n");

				//// Read data
				//auto now = esp_timer_get_time();
				//adcController.ReadSingle(singleSensorHistory.data(), singleSensorHistory.size(), 1800);
				//auto fin = esp_timer_get_time();

				//// Notify host of finished capture
				//write(1, "\004\004\004\004\004\004\004\004", 8);
				//auto diff = fin - now;

				//// Notify host of beginning transaction
				//write(1, "\027\027\027\027\027\027\027\027", 8);

				//std::array<char, 4> sensorName{};
				//memcpy(sensorName.data(), mode_params::singleSensorMonitoringSensor.GetName(), strlen(mode_params::singleSensorMonitoringSensor.GetName()));
				//WriteEnc(sensorName.data(), sensorName.size());

				//WriteEnc(&calibration::calibrationData[mode_params::singleSensorMonitoringSensor].min, sizeof(double));
				//WriteEnc(&calibration::calibrationData[mode_params::singleSensorMonitoringSensor].max, sizeof(double));
				//WriteEnc(&diff, sizeof(diff));
				//uint32_t dataPoints = singleSensorHistory.size();
				//WriteEnc(&dataPoints, sizeof(dataPoints));
				//WriteEnc(&singleSensorHistory, sizeof(singleSensorHistory));
			//}
#endif
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
					Application::instance->GetOnSensorStateChangeSignal().publish(*this, key);
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

		case Mode::SingleSensorMonitoring: {
#ifdef ENABLE_SINGLE_SENSOR_MONITORING
			//adcController.SetAdcModeSingle();
			//InitSingleSensorHistory();
			write(1, "\004\004\004\004\004\004\004\004", 8);
			std::array<char, 4> sensorName{};
			memcpy(sensorName.data(), mode_params::singleSensorMonitoringSensor.GetName(), strlen(mode_params::singleSensorMonitoringSensor.GetName()));
			WriteEnc(sensorName.data(), sensorName.size());
			WriteEnc(&calibration::calibrationData[mode_params::singleSensorMonitoringSensor].min, sizeof(double));
			WriteEnc(&calibration::calibrationData[mode_params::singleSensorMonitoringSensor].max, sizeof(double));

			fflush(stdin);
			fflush(stdout);

			auto now = esp_timer_get_time();
			fmt::print("recording {} in 1 sec...\n", mode_params::singleSensorMonitoringSensor.GetName());
			write(1, "\005\005\005\005\005\005\005\005", 8);
			while (esp_timer_get_time() - now < 1000000) {
				; // wait
			}
			fmt::print("recording\n");
#endif
			break;
		}

		default: {
			adcController.SetAdcModeAuto();
			adcController.Read(tmpData, 512);
			InitLogicStates(tmpData);
			break;
		}
	}
}


} // namespace opkey
