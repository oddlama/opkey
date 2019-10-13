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
		{ { -0.1277480572462081909179688,  0.3304865956306457519531250, -0.4712223112583160400390625, -0.2413977235555648803710938,  0.4912044405937194824218750,  0.1684632748365402221679688 }
		, { -0.1105740889906883239746094, -0.0976749062538146972656250, -0.6702753305435180664062500, -0.1022265180945396423339844,  0.5015703439712524414062500, -0.1292583793401718139648438 }
		, {  0.0358082577586174011230469, -0.7551938295364379882812500, -0.4502839744091033935546875, -0.5191339254379272460937500, -0.0589177869260311126708984, -0.4515191912651062011718750 }
		, {  0.0115315550938248634338379, -0.6794781684875488281250000, -0.3843287825584411621093750, -0.1550090014934539794921875, -0.0114254672080278396606445, -0.3727123141288757324218750 }
		, { -0.0153518440201878547668457, -0.1743119359016418457031250, -0.1104588061571121215820312,  0.0460317283868789672851562, -0.0178040564060211181640625, -0.1623159199953079223632812 }
		, {  0.2064742445945739746093750, -0.0363417342305183410644531,  0.0337507799267768859863281,  0.2835503220558166503906250,  0.0465579144656658172607422,  0.0179813504219055175781250 }
		, {  0.1055821254849433898925781,  0.2698545455932617187500000,  0.0225708670914173126220703,  0.6245223879814147949218750, -0.0304941516369581222534180,  0.3023249804973602294921875 }
		, {  0.1371037214994430541992188,  0.6365053653717041015625000,  0.0020911048632115125656128,  0.5741496086120605468750000, -0.0608852095901966094970703,  0.1853836774826049804687500 }
		, {  0.2241828292608261108398438,  0.2379029542207717895507812, -0.0412591062486171722412109,  0.5232817530632019042968750, -0.1450323015451431274414062, -0.0634911283850669860839844 }
		, {  0.3514463603496551513671875,  0.1320793330669403076171875,  0.0635384172201156616210938,  0.3642631769180297851562500, -0.0889912024140357971191406, -0.3804521560668945312500000 }
		, {  0.5679351687431335449218750, -0.1195221915841102600097656,  0.5065813660621643066406250,  0.5741807818412780761718750,  0.1303230226039886474609375, -0.1497906744480133056640625 }
		, {  0.5532039999961853027343750, -0.5099382400512695312500000,  0.4991352260112762451171875,  0.9813601970672607421875000,  0.4012228250503540039062500,  0.7670742273330688476562500 }
		, {  0.3815183043479919433593750, -0.6512806415557861328125000,  0.3483542799949645996093750,  0.9419487714767456054687500,  0.5379822850227355957031250,  0.8130189180374145507812500 }
		, {  0.1817216575145721435546875, -0.5659379959106445312500000,  0.1820287704467773437500000,  0.4327642917633056640625000,  0.5397279858589172363281250,  0.2827410101890563964843750 }
		, {  0.0378653034567832946777344, -0.3351432681083679199218750, -0.2183155715465545654296875, -0.1762653738260269165039062,  0.3225080966949462890625000, -0.0936106517910957336425781 }
		, { -0.2579010426998138427734375, -0.0609211958944797515869141, -0.1944268792867660522460938, -0.6531740427017211914062500, -0.0431330092251300811767578,  0.2856881916522979736328125 }
		}};
	static constexpr const std::array<double, 6> dense0_biases =
		{  1.6867442131042480468750000,  0.1589663028717041015625000, -0.7504151463508605957031250,  0.3376105725765228271484375, -1.2553795576095581054687500,  1.4488780498504638671875000 };
	static constexpr const std::array<std::array<double, 1>, 6> dense1_weights = {
		{ { -0.7682641148567199707031250 }
		, { -0.6598582863807678222656250 }
		, {  0.9922219514846801757812500 }
		, {  0.6336081624031066894531250 }
		, {  0.9885115623474121093750000 }
		, { -0.7050668001174926757812500 }
		}};
	static constexpr const std::array<double, 1> dense1_biases =
		{  0.1403302848339080810546875 };
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
