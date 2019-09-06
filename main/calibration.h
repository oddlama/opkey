#pragma once

#include "config.h"
#include "sensor_tensor.h"


namespace opkey::calibration {


enum class CalibrationStatus {
	InvalidMinMax,
	MissingFirstUpdate,
	MissingUsage,
	RangeToSmall,
	Calibrated
};


struct SensorCalibrationData {
	double min = 1.0;
	double max = 0.0;
	double range = -1.0;

	// true if the last update was the min value, false if it was max
	bool lastUpdateWasMin = false;
	// Amount of falling edges on lastUpdateWasMin.
	// (i.e. amount of performed update cycles, where a cycle
	// corresponds to an update in both min and max)
	uint16_t updateCycles = 0;
	// If the sensor is currently close to the max boundary
	bool closeToMaxBoundary = false;
	// Amount of times a significant positive change in sensor
	// value was recorded
	uint16_t usageCycles = 0;

	double Apply(double val) {
		return (val - min) / range;
	}

	/** Returns the current calibration status */
	CalibrationStatus GetCalibrationStatus() const noexcept {
		if (min > max) {
			return CalibrationStatus::InvalidMinMax;
		}

		if (updateCycles < 1) {
			return CalibrationStatus::MissingFirstUpdate;
		}

		if (usageCycles < config::requiredCalibrationCycles) {
			return CalibrationStatus::MissingUsage;
		}

		if (range < config::minimumSensorValueCoverage) {
			return CalibrationStatus::RangeToSmall;
		}

		return CalibrationStatus::Calibrated;
	}
};

using CalibrationData = SensorTensor<SensorCalibrationData>;

extern CalibrationData calibrationData;

void Reset();
void Load();
void Save();
void Print();
bool Calibrate(SensorData& newData);


} // namespace opkey::calibration
