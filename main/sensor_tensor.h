#pragma once

#include "sensor.h"

#include <array>


namespace opkey {


template<typename T>
class SensorTensor : public std::array<T, 90> {
public:
	using Base = std::array<T, 90>;
	using const_reference = typename Base::const_reference;
	using reference = typename Base::reference;
	using size_type = typename Base::size_type;

	inline constexpr const_reference operator[](size_t pos) const {
		return Base::operator[](pos);
	}

	inline constexpr reference operator[](size_t pos) {
		return Base::operator[](pos);
	}

	inline constexpr const_reference operator[](Sensor pos) const {
		return Base::operator[](static_cast<size_t>(pos));
	}

	inline constexpr reference operator[](Sensor pos) {
		return Base::operator[](static_cast<size_t>(pos));
	}
};


/**
 * Raw sensor data.
 */
using RawSensorData = SensorTensor<uint16_t>;
using SensorData = SensorTensor<double>;


/**
 * Logical state which is calculated based on the captured
 * history of sensor data
 */
struct LogicState {
	// Current position
	double pos = 0.0;

	// Key/Pedal state has changed regarding to the last known state
	bool changed = false;
	// Key/Pedal is currently pressed
	bool pressed = false;

	// Last known time this key/pedal was pressed
	int64_t lastPressTime = 0;
	// Key/Pedal press-hit velocity
	double pressVelocity = 0.0;
	// Last known time this key/pedal was released
	int64_t lastReleaseTime = 0;

	// Time of key rising above posLowThreshold
	int64_t lowRisingEdgeTime = 0;
	// Key position at low rising edge
	double lowRisingEdgePos = 0.0;

	// Time of key rising above posControlThreshold
	int64_t controlRisingEdgeTime = 0;
	// Key position at control rising edge
	double controlRisingEdgePos = 0.0;
};

using SensorLogicStateData = SensorTensor<LogicState>;


} // namespace opkey
