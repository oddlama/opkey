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
	double lowThreshold = 0.2;
	double highThreshold = 0.8;

	for (size_t i = 0; i < newData.size(); ++i) {
		auto& state = logicStates[i];

		// 1. Swizzle the raw data to match the sensor order
		// 2. Position is sqrt(data), because light intensity is 1/(distance^2)
		auto rawPos = sqrt(newData[config::GetSensorSwizzle(i)]);
		// 3. Apply calibration
		auto prevPos = state.pos;
		state.pos = calibration::calibrationData[i].Apply(rawPos);

		if (state.pressed) {
			if (state.pos < lowThreshold) {
				// The key was pressed and the position is now
				// below the low threshold, so it is now released
				state.pressed = false;
				state.changed = true;
				state.lastReleaseTime = now;
			}
		} else {
			if (prevPos < lowThreshold && state.pos >= lowThreshold) {
				// Key was not pressed and the position is
				// the first past the low threshold
				state.lowRisingEdgeTime = now;
				state.lowRisingEdgePos = state.pos;
			} else if (state.pos >= highThreshold) {
				// Key was not pressed and the position is
				// past the high threshold, therefore the key is
				// now pressed.
				auto risingEdgeDeltaTime = now - state.lowRisingEdgeTime;
				state.pressed = true;
				state.changed = true;
				state.lastPressTime = now;
				state.pressVelocity = (state.pos - state.lowRisingEdgePos) * 1000000.0 / risingEdgeDeltaTime;
				fmt::print("key[0x{:02x}, {:2d}, {:4s}] down  curPos: {:7.2f} vel: {:7.2f}\n",
						Sensor{i}.GetIndex(),
						Sensor{i}.GetIndex(),
						Sensor{i}.GetName(),
						state.pos, state.pressVelocity);
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
				fmt::print("3...\n");
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				fmt::print("2...\n");
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				write(1, "\005\005\005\005\005\005\005\005", 8);
				fmt::print("1...\n");
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				fmt::print("NOW!\n");
				auto now = esp_timer_get_time();
				adcController.ReadSingle(singleSensorHistory.data(), singleSensorHistory.size());
				auto fin = esp_timer_get_time();
				write(1, "\004\004\004\004\004\004\004\004", 8);
				auto diff = fin - now;
				write(1, "\027\027\027\027\027\027\027\027", 8);
				char sensorName[4];
				memset(sensorName, 0, 4);
				memcpy(sensorName, mode_params::singleSensorMonitoringSensor.GetName(), strlen(mode_params::singleSensorMonitoringSensor.GetName()));
				write(1, sensorName, 4);
				write(1, &diff, sizeof(diff));
				//write(1, singleSensorHistory.data(), sizeof(singleSensorHistory));
				for (auto& d : singleSensorHistory) {
					uint32_t expanded =
						((((d & 0x000f) >>  0) + 'a') <<  0) |
						((((d & 0x00f0) >>  4) + 'a') <<  8) |
						((((d & 0x0f00) >>  8) + 'a') << 16) |
						((((d & 0xf000) >> 12) + 'a') << 24);
					write(1, &expanded, sizeof(expanded));
				}
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
