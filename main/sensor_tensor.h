#pragma once

#include "sensor.h"

#include <array>


namespace OpKey {


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
 * Kinematic sensor data calculated from raw value and
 * previous data points.
 */
struct SensorKinematicData {
	SensorTensor<double> position{};
	SensorTensor<double> velocity{};
	SensorTensor<double> acceleration{};
};

/**
 * Logical state which is calculated based on the captured
 * history of sensor data
 */
struct LogicState {
	// Key/Pedal is currently pressed
	bool pressed = false;
	// Key/Pedal state has changed regarding to the last known state
	bool changed = false;
	// Last known time this key/pedal was pressed
	int64_t lastPressTime = -1;
	// Last known time this key/pedal was released
	int64_t lastReleaseTime = -1;
};

using SensorLogicStateData = SensorTensor<LogicState>;

struct SensorDataCollection {
	int64_t timestamp = -1;
	SensorData raw{};
	SensorKinematicData kinematic{};
	SensorLogicStateData keyState{};

	/** Checks if this contains valid data */
	operator bool() const noexcept {
		return timestamp >= 0;
	}
};


} // namespace OpKey
