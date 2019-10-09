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
	// Time of last update
	int64_t lastUpdateTime = 0;
	uint16_t delta = 0;
	uint16_t rawPos = 0;
	// Current position
	double pos = 0.0;
	// Current velocity
	double vel = 0.0;
	// Exponential moving average of velocity = EMA(vel)
	double velEma = 0.0;

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

	// Time at which the velocity reached a maximum
	int64_t maxVelTime = 0;
	// The velocity value at its maximum
	double maxVel = 0.0;
	// The EMA(vel) at the velocity maximum
	double maxVelEma = 0.0;
	// The pos at the velocity maximum
	double maxVelPos = 0.0;
};

using SensorLogicStateData = SensorTensor<LogicState>;


} // namespace opkey
