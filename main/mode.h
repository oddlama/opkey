#pragma once

#include "sensor.h"


namespace opkey {


namespace mode_params {

inline Sensor singleSensorMonitoringSensor{};

} // namespace mode_params


enum class Mode : uint8_t {
	Idle,
	LoadConfig,
	NormalOperation,
	Calibrate,
	SingleSensorMonitoring,
	_EnumMax,
};


} // namespace opkey
