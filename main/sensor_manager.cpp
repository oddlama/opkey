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
	auto prevPos = state.posHistory[state.posHistoryCurrent];
	auto prevVel = state.vel;

	// 1. Position is sqrt(data), because light intensity is 1/(distance^2)
	// 2. Apply calibration
	auto rawPos = sqrt(newData);
	state.pos = calibration::calibrationData[sensor].Apply(rawPos);
	state.vel = (state.pos - prevPos) * (1000000.0 / deltaTime);

	// Save pos in history
	if (++state.posHistoryCurrent == state.posHistory.size()) {
		state.posHistoryCurrent = 0;
	}
	state.posHistory[state.posHistoryCurrent] = state.pos;

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
					state.pressVelocity = CalculatePressVelocity(state);
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
				}
			}
		}
	}
}

double SensorManager::CalculatePressVelocity(const LogicState& state) {
	auto modelBegin = esp_timer_get_time();
	std::array<double, 16> x{};
	static_assert(x.size() == state.posHistory.size(), "Mismatching position history sizes");

	auto from = state.posHistoryCurrent + 1;
	auto to = from + state.posHistory.size();

	double* xPtr = x.data() + x.size();
	for (int i = from; i < to; ++i) {
		*--xPtr = state.posHistory[i % state.posHistory.size()] * 2.0 - 1.0;
	}

	// -------- BEGIN GENERATED KERAS MODEL EVALUATION --------
	static constexpr const std::array<std::array<double, 6>, 16> dense0_weights = {
		{ { -0.127748057246208190918,  0.330486595630645751953, -0.471222311258316040039, -0.241397723555564880371,  0.491204440593719482422,  0.168463274836540222168 }
		, { -0.110574088990688323975, -0.097674906253814697266, -0.670275330543518066406, -0.102226518094539642334,  0.501570343971252441406, -0.129258379340171813965 }
		, {  0.035808257758617401123, -0.755193829536437988281, -0.450283974409103393555, -0.519133925437927246094, -0.058917786926031112671, -0.451519191265106201172 }
		, {  0.011531555093824863434, -0.679478168487548828125, -0.384328782558441162109, -0.155009001493453979492, -0.011425467208027839661, -0.372712314128875732422 }
		, { -0.015351844020187854767, -0.174311935901641845703, -0.110458806157112121582,  0.046031728386878967285, -0.017804056406021118164, -0.162315919995307922363 }
		, {  0.206474244594573974609, -0.036341734230518341064,  0.033750779926776885986,  0.283550322055816650391,  0.046557914465665817261,  0.017981350421905517578 }
		, {  0.105582125484943389893,  0.269854545593261718750,  0.022570867091417312622,  0.624522387981414794922, -0.030494151636958122253,  0.302324980497360229492 }
		, {  0.137103721499443054199,  0.636505365371704101562,  0.002091104863211512566,  0.574149608612060546875, -0.060885209590196609497,  0.185383677482604980469 }
		, {  0.224182829260826110840,  0.237902954220771789551, -0.041259106248617172241,  0.523281753063201904297, -0.145032301545143127441, -0.063491128385066986084 }
		, {  0.351446360349655151367,  0.132079333066940307617,  0.063538417220115661621,  0.364263176918029785156, -0.088991202414035797119, -0.380452156066894531250 }
		, {  0.567935168743133544922, -0.119522191584110260010,  0.506581366062164306641,  0.574180781841278076172,  0.130323022603988647461, -0.149790674448013305664 }
		, {  0.553203999996185302734, -0.509938240051269531250,  0.499135226011276245117,  0.981360197067260742188,  0.401222825050354003906,  0.767074227333068847656 }
		, {  0.381518304347991943359, -0.651280641555786132812,  0.348354279994964599609,  0.941948771476745605469,  0.537982285022735595703,  0.813018918037414550781 }
		, {  0.181721657514572143555, -0.565937995910644531250,  0.182028770446777343750,  0.432764291763305664062,  0.539727985858917236328,  0.282741010189056396484 }
		, {  0.037865303456783294678, -0.335143268108367919922, -0.218315571546554565430, -0.176265373826026916504,  0.322508096694946289062, -0.093610651791095733643 }
		, { -0.257901042699813842773, -0.060921195894479751587, -0.194426879286766052246, -0.653174042701721191406, -0.043133009225130081177,  0.285688191652297973633 }
		}};
	static constexpr const std::array<double, 6> dense0_biases =
		{  0.285688191652297973633,  0.285688191652297973633,  0.285688191652297973633,  0.285688191652297973633,  0.285688191652297973633,  0.285688191652297973633 };
	static constexpr const std::array<std::array<double, 1>, 6> dense1_weights = {
		{ { -0.768264114856719970703 }
		, { -0.659858286380767822266 }
		, {  0.992221951484680175781 }
		, {  0.633608162403106689453 }
		, {  0.988511562347412109375 }
		, { -0.705066800117492675781 }
		}};
	static constexpr const std::array<double, 1> dense1_biases =
		{ -0.705066800117492675781 };
	double mul0_0x0 =
		x[ 0] * dense0_weights[ 0][ 0] +
		x[ 1] * dense0_weights[ 1][ 0] +
		x[ 2] * dense0_weights[ 2][ 0] +
		x[ 3] * dense0_weights[ 3][ 0] +
		x[ 4] * dense0_weights[ 4][ 0] +
		x[ 5] * dense0_weights[ 5][ 0] +
		x[ 6] * dense0_weights[ 6][ 0] +
		x[ 7] * dense0_weights[ 7][ 0] +
		x[ 8] * dense0_weights[ 8][ 0] +
		x[ 9] * dense0_weights[ 9][ 0] +
		x[10] * dense0_weights[10][ 0] +
		x[11] * dense0_weights[11][ 0] +
		x[12] * dense0_weights[12][ 0] +
		x[13] * dense0_weights[13][ 0] +
		x[14] * dense0_weights[14][ 0] +
		x[15] * dense0_weights[15][ 0];
	double mul0_0x1 =
		x[ 0] * dense0_weights[ 0][ 1] +
		x[ 1] * dense0_weights[ 1][ 1] +
		x[ 2] * dense0_weights[ 2][ 1] +
		x[ 3] * dense0_weights[ 3][ 1] +
		x[ 4] * dense0_weights[ 4][ 1] +
		x[ 5] * dense0_weights[ 5][ 1] +
		x[ 6] * dense0_weights[ 6][ 1] +
		x[ 7] * dense0_weights[ 7][ 1] +
		x[ 8] * dense0_weights[ 8][ 1] +
		x[ 9] * dense0_weights[ 9][ 1] +
		x[10] * dense0_weights[10][ 1] +
		x[11] * dense0_weights[11][ 1] +
		x[12] * dense0_weights[12][ 1] +
		x[13] * dense0_weights[13][ 1] +
		x[14] * dense0_weights[14][ 1] +
		x[15] * dense0_weights[15][ 1];
	double mul0_0x2 =
		x[ 0] * dense0_weights[ 0][ 2] +
		x[ 1] * dense0_weights[ 1][ 2] +
		x[ 2] * dense0_weights[ 2][ 2] +
		x[ 3] * dense0_weights[ 3][ 2] +
		x[ 4] * dense0_weights[ 4][ 2] +
		x[ 5] * dense0_weights[ 5][ 2] +
		x[ 6] * dense0_weights[ 6][ 2] +
		x[ 7] * dense0_weights[ 7][ 2] +
		x[ 8] * dense0_weights[ 8][ 2] +
		x[ 9] * dense0_weights[ 9][ 2] +
		x[10] * dense0_weights[10][ 2] +
		x[11] * dense0_weights[11][ 2] +
		x[12] * dense0_weights[12][ 2] +
		x[13] * dense0_weights[13][ 2] +
		x[14] * dense0_weights[14][ 2] +
		x[15] * dense0_weights[15][ 2];
	double mul0_0x3 =
		x[ 0] * dense0_weights[ 0][ 3] +
		x[ 1] * dense0_weights[ 1][ 3] +
		x[ 2] * dense0_weights[ 2][ 3] +
		x[ 3] * dense0_weights[ 3][ 3] +
		x[ 4] * dense0_weights[ 4][ 3] +
		x[ 5] * dense0_weights[ 5][ 3] +
		x[ 6] * dense0_weights[ 6][ 3] +
		x[ 7] * dense0_weights[ 7][ 3] +
		x[ 8] * dense0_weights[ 8][ 3] +
		x[ 9] * dense0_weights[ 9][ 3] +
		x[10] * dense0_weights[10][ 3] +
		x[11] * dense0_weights[11][ 3] +
		x[12] * dense0_weights[12][ 3] +
		x[13] * dense0_weights[13][ 3] +
		x[14] * dense0_weights[14][ 3] +
		x[15] * dense0_weights[15][ 3];
	double mul0_0x4 =
		x[ 0] * dense0_weights[ 0][ 4] +
		x[ 1] * dense0_weights[ 1][ 4] +
		x[ 2] * dense0_weights[ 2][ 4] +
		x[ 3] * dense0_weights[ 3][ 4] +
		x[ 4] * dense0_weights[ 4][ 4] +
		x[ 5] * dense0_weights[ 5][ 4] +
		x[ 6] * dense0_weights[ 6][ 4] +
		x[ 7] * dense0_weights[ 7][ 4] +
		x[ 8] * dense0_weights[ 8][ 4] +
		x[ 9] * dense0_weights[ 9][ 4] +
		x[10] * dense0_weights[10][ 4] +
		x[11] * dense0_weights[11][ 4] +
		x[12] * dense0_weights[12][ 4] +
		x[13] * dense0_weights[13][ 4] +
		x[14] * dense0_weights[14][ 4] +
		x[15] * dense0_weights[15][ 4];
	double mul0_0x5 =
		x[ 0] * dense0_weights[ 0][ 5] +
		x[ 1] * dense0_weights[ 1][ 5] +
		x[ 2] * dense0_weights[ 2][ 5] +
		x[ 3] * dense0_weights[ 3][ 5] +
		x[ 4] * dense0_weights[ 4][ 5] +
		x[ 5] * dense0_weights[ 5][ 5] +
		x[ 6] * dense0_weights[ 6][ 5] +
		x[ 7] * dense0_weights[ 7][ 5] +
		x[ 8] * dense0_weights[ 8][ 5] +
		x[ 9] * dense0_weights[ 9][ 5] +
		x[10] * dense0_weights[10][ 5] +
		x[11] * dense0_weights[11][ 5] +
		x[12] * dense0_weights[12][ 5] +
		x[13] * dense0_weights[13][ 5] +
		x[14] * dense0_weights[14][ 5] +
		x[15] * dense0_weights[15][ 5];
	double add0_0 = mul0_0x0 + dense0_biases[ 0];
	double add0_1 = mul0_0x1 + dense0_biases[ 1];
	double add0_2 = mul0_0x2 + dense0_biases[ 2];
	double add0_3 = mul0_0x3 + dense0_biases[ 3];
	double add0_4 = mul0_0x4 + dense0_biases[ 4];
	double add0_5 = mul0_0x5 + dense0_biases[ 5];
	double relu0_0 = add0_0 < 0.0 ? 0.0 : add0_0;
	double relu0_1 = add0_1 < 0.0 ? 0.0 : add0_1;
	double relu0_2 = add0_2 < 0.0 ? 0.0 : add0_2;
	double relu0_3 = add0_3 < 0.0 ? 0.0 : add0_3;
	double relu0_4 = add0_4 < 0.0 ? 0.0 : add0_4;
	double relu0_5 = add0_5 < 0.0 ? 0.0 : add0_5;
	double mul1_0x0 =
		relu0_0 * dense1_weights[ 0][ 0] +
		relu0_1 * dense1_weights[ 1][ 0] +
		relu0_2 * dense1_weights[ 2][ 0] +
		relu0_3 * dense1_weights[ 3][ 0] +
		relu0_4 * dense1_weights[ 4][ 0] +
		relu0_5 * dense1_weights[ 5][ 0];
	double add1_0 = mul1_0x0 + dense1_biases[ 0];
	double tanh1_0 = tanh(add1_0);
	double y_0 = (tanh1_0 + 1.0) / 2.0;
	// -------- END GENERATED KERAS MODEL EVALUATION --------

	auto modelEnd = esp_timer_get_time();
	fmt::print("model evaluation took {}us, y = {}\n", modelEnd - modelBegin, y_0);
	return y_0;
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
