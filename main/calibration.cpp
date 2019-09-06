#include "calibration.h"
#include "application.h"

#include <array>
#include <string_view>


namespace opkey::calibration {


CalibrationData calibrationData{};


void Reset() {
	calibrationData = CalibrationData{};
	fmt::print("TODO started calibration\n");
}

void Load() {
	//TODO
	//if (has calibration data) {
	//} else {
		if (Application::instance->GetNextMode() != Mode::NormalOperation) {
			esp::loge("Calibration is necessary, but next mode is already set. Forcing calibration.");
		}
		Application::instance->SetNextMode(Mode::Calibrate);
	//}
}

void Save() {
	static std::array<char, 48> barBuffer{};

	Sensor::ForEach([&](Sensor s) {
		auto& c = calibrationData[s];
		fmt::print("{:2d}: ", s.GetIndex());
		switch (c.GetCalibrationStatus()) {
			case CalibrationStatus::InvalidMinMax:       fmt::print("InvalidMinMax\n"); break;
			case CalibrationStatus::MissingFirstUpdate:  fmt::print("MissingFirstUpdate\n"); break;
			default: {
				std::memset(barBuffer.data(), '-', barBuffer.size());
				int from = static_cast<int>(barBuffer.size() * c.min);
				int to = static_cast<int>(barBuffer.size() * c.max);
				std::memset(barBuffer.data() + from, '#', to - from);
				fmt::print("[{}] min={:<7.2f} max={:<7.2f} range={:<7.2f} updateCycles={:<4d} usageCycles={:<4d}\n"
					, std::string_view{barBuffer.data(), barBuffer.size()}
					, 100 * (c.min)
					, 100 * (c.max)
					, 100 * (c.range)
					, c.updateCycles
					, c.usageCycles);
				break;
			}
		}
	});
	// TODO print calibration,
	// // TODO logarithmic compensation!!!!!
	// 0: min 0, max 2345, effective bits: log2(max-min), percentage
	// raw      [------################----------------]
	// distance [------################----------------]
	// 1 at min = x distance
	// 1 at max = x distance
}

bool Calibrate(SensorData& newData) {
	// Swizzle the raw data to match the sensor order
	bool allSensorsCalibrated = true;
					auto now = esp_timer_get_time();
					static long last = 0;
	for (size_t i = 0; i < newData.size(); ++i) {
		if (now - last > 5000000) {
			last = now;
			Save();
		}
		auto& val = newData[config::GetSensorSwizzle(i)];
		auto& c = calibrationData[i];
		if (val > c.max) {
			c.max = val;
			c.range = c.max - c.min;
			// Falling edge -> increment update cycles
			if (c.lastUpdateWasMin) {
				++c.updateCycles;
			}
			c.lastUpdateWasMin = false;
		}
		if (val < c.min) {
			c.min = val;
			c.range = c.max - c.min;
			c.lastUpdateWasMin = true;
		}

		if (c.updateCycles > 0 && c.range > config::calibrationNearBoundaryMinRange) {
			double valuePercentage = (val - c.min) / c.range;
			if (valuePercentage <= config::calibrationNearBoundaryThreshold) {
				// We are near the minimum
				c.closeToMaxBoundary = false;
			} else if ((1.0 - valuePercentage) <= config::calibrationNearBoundaryThreshold) {
				// We are near the maximum
				if (not c.closeToMaxBoundary) {
					// The key has significantly travelled (from min to max)
					++c.usageCycles;
				}
				c.closeToMaxBoundary = true;
			}
		}

		if (c.GetCalibrationStatus() != CalibrationStatus::Calibrated) {
			allSensorsCalibrated = false;
		}
	}

	return allSensorsCalibrated;
}


} // namespace opkey::calibration
