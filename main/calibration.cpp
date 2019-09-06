#include "calibration.h"
#include "application.h"
#include "nvs.h"

#include <array>
#include <string_view>


namespace opkey::calibration {


inline constexpr const char* nvsKeyCalibration = "sensorCalibr";

CalibrationData calibrationData{};


void Reset() {
	calibrationData = CalibrationData{};
	fmt::print("Calibration reset\n");
}

void Load() {
	if (nvs::Open().Get(nvsKeyCalibration, calibrationData)) {
		esp::logi("Loaded sensor calibration data");
	} else {
		if (Application::instance->GetNextMode() != Mode::NormalOperation) {
			esp::loge("Calibration is necessary, but next mode is already set. Forcing calibration.");
		}
		Application::instance->SetNextMode(Mode::Calibrate);
	}
}

void Save() {
	nvs::Open().Set(nvsKeyCalibration, calibrationData);
	fmt::print("Calibration saved\n");
}

void Print() {
	static std::array<char, 48> barBuffer{};

	Sensor::ForEach([&](Sensor s) {
		std::memset(barBuffer.data(), '-', barBuffer.size());
		auto& c = calibrationData[s];

#define OPKEY_COPY_CSTR(arr, str) std::copy(str, str + strlen(str), arr.data());

		fmt::print("{:4s} ", s.GetName());
		switch (c.GetCalibrationStatus()) {
			case CalibrationStatus::InvalidMinMax:      OPKEY_COPY_CSTR(barBuffer, "InvalidMinMax"); break;
			case CalibrationStatus::MissingFirstUpdate: OPKEY_COPY_CSTR(barBuffer, "MissingFirstUpdate"); break;
			default: {
				int from = static_cast<int>(barBuffer.size() * c.min);
				int to = static_cast<int>(barBuffer.size() * c.max);
				std::memset(barBuffer.data() + from, '#', to - from);
				break;
			}
		}

#undef OPKEY_COPY_CSTR

		fmt::print("[{:48s}] in [{:6.2f},{:6.2f}] cov={:6.2f}% upd={:2d} use={:2d}"
			, std::string_view{barBuffer.data(), barBuffer.size()}
			, 100.0 * c.min
			, 100.0 * c.max
			, 100.0 * c.range
			, c.updateCycles
			, c.usageCycles);

		if (s.GetIndex() % 2 == 0) {
			fmt::print("    ");
		} else {
			fmt::print("\n");
		}
	});

	if constexpr (Sensor::totalCount % 2 == 1) {
		fmt::print("\n");
	}

	// TODO logarithmic compensation!!!!!
	// TODO effective bits
	// TODO effective range
}

bool Calibrate(SensorData& newData) {
	bool allSensorsCalibrated = true;
	for (size_t i = 0; i < newData.size(); ++i) {
		// Swizzle the raw data to match the sensor order
		auto& val = newData[config::GetSensorSwizzle(i)];
		auto& c = calibrationData[i];

		// Update max
		if (val > c.max) {
			c.max = val;
			c.range = c.max - c.min;

			// Falling edge -> increment update cycles
			if (c.lastUpdateWasMin) {
				++c.updateCycles;
			}
			c.lastUpdateWasMin = false;
		}

		// Update min
		if (val < c.min) {
			c.min = val;
			c.range = c.max - c.min;
			c.lastUpdateWasMin = true;
		}

		// Update usage cycles
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
