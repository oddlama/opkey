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
 * Initialize the history with the given valid data
 */
void SensorManager::InitHistory(SensorData& newData) {
	OPKEY_PROFILE_FUNCTION();

	// Clean initial state
	history = SensorHistory<HistorySize>{};

	for (int i = 0; i < history.Size(); ++i) {
		CalculateNextSensorState(newData);
	}
}

void SensorManager::InitSingleSensorHistory() {
	singleSensorHistory = {};
}

void SensorManager::CalculateNextSensorState(SensorData& newData) {
	OPKEY_PROFILE_FUNCTION();

	auto& t_0 = history.NextSlot();
	auto& t_1 = history[-1]; // Previous state

	auto now = esp_timer_get_time();
	t_0.timestamp = now;

	// Swizzle the raw data to match the sensor order
	for (size_t i = 0; i < newData.size(); ++i) {
		t_0.raw[i] = newData[config::GetSensorSwizzle(i)];
	}

	// Inverse delta time between now and t_1 in [1/s]
	double dt = 1000000.0 / (t_0.timestamp - t_1.timestamp);

	for (size_t i = 0; i < newData.size(); ++i) {
		// Position is sqrt(data), because light intensity is 1/(distance^2)
		// TODO normalize data based on calibration
		// TODO position = sqrt(ApplyCalibration(newData[i], i));
		t_0.kinematic.position[i] = sqrt(t_0.raw[i]);
		t_0.kinematic.velocity[i] = (t_0.kinematic.position[i] - t_1.kinematic.position[i]) * dt;
		t_0.kinematic.acceleration[i] = (t_0.kinematic.velocity[i] - t_1.kinematic.velocity[i]) * dt;

		t_0.keyState[i] = t_1.keyState[i];
		if ((not t_1.keyState[i].pressed && t_0.kinematic.position[i] > 0.4 && t_0.kinematic.velocity[i] > 2.0)) {
			t_0.keyState[i].pressed = true;
		} else if (t_1.keyState[i].pressed && t_0.kinematic.position[i] < 0.4) {
			t_0.keyState[i].pressed = false;
		}
		t_0.keyState[i].changed = (t_0.keyState[i].pressed != t_1.keyState[i].pressed);
		if (t_0.keyState[i].changed) {
			if (t_0.keyState[i].pressed) {
				t_0.keyState[i].lastPressTime = now;
			} else {
				t_0.keyState[i].lastReleaseTime = now;
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
			fmt::print("3...\n");
			vTaskDelay(1000 / portTICK_PERIOD_MS);
			fmt::print("2...\n");
			vTaskDelay(1000 / portTICK_PERIOD_MS);
			write(1, "~~~~~~~~", 8);
			fmt::print("1...\n");
			vTaskDelay(1000 / portTICK_PERIOD_MS);
			fmt::print("SAMPLING!\n");
			auto now = esp_timer_get_time();
			adcController.ReadSingle(singleSensorHistory.data(), singleSensorHistory.size());
			auto fin = esp_timer_get_time();
			write(1, "========", 8);
			fmt::print("time (total {:d}us), {:4s}, sqrt({:4s})\n", fin - now, mode_params::singleSensorMonitoringSensor.GetName(), mode_params::singleSensorMonitoringSensor.GetName());
			auto diff = fin - now;
			write(1, ">>>>>>>>", 8);
			char sensorName[4];
			memset(sensorName, 0, 4);
			memcpy(sensorName, mode_params::singleSensorMonitoringSensor.GetName(), strlen(mode_params::singleSensorMonitoringSensor.GetName()));
			write(1, sensorName, 4);
			write(1, &diff, sizeof(diff));
			for (auto& d : singleSensorHistory) {
				uint32_t expanded =
					((((d & 0x000f) >>  0) + 'a') <<  0) |
					((((d & 0x00f0) >>  4) + 'a') <<  8) |
					((((d & 0x0f00) >>  8) + 'a') << 16) |
					((((d & 0xf000) >> 12) + 'a') << 24);
				write(1, &expanded, sizeof(expanded));
			}
			fmt::print("\nsample time {:d}us\n", fin - now);
			vTaskDelay(5000 / portTICK_PERIOD_MS);
			break;
		}

		case Mode::NormalOperation: {
			// TODO settings for samples
			adcController.Read(tmpData, 2);
			CalculateNextSensorState(tmpData);

			// Notify listeners if a key state has changed
			const auto& t_0 = history[0];
			Sensor::ForEachKey([&](Sensor key) {
				if (t_0.keyState[key].changed) {
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
			// Initialize history with valid data
			adcController.Read(tmpData, 512);
			InitHistory(tmpData);
			break;
		}
	}
}


} // namespace opkey
