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


} // namespace OpKey
