#pragma once

#include "config.h"
#include "profiler.h"
#include "fmt.h"
#include "sensor.h"
#include "sensor_tensor.h"

#include <esp_timer.h>

#include <stdexcept>
#include <array>


namespace opkey {


/**
 * A class to store the last N points of sensor data, and
 * the corresponding logical state
 */
template<size_t N>
class SensorHistory {
	static_assert(N >= 2, "SensorHistory may not contain less than 2 data points");

public:
	/**
	 * Retrieves data from the history, with 0 denoting the newest
	 * history entry and size() - 1 the second newest.
	 * Accessing negative elements is allowed. -1 will give the previous and (-size() + 1) the oldest
	 */
	inline SensorDataCollection& Get(int index) {
		if (index < 0) {
			index += Size();
		}
		if (index < 0 || index >= Size()) {
			throw std::out_of_range("Cannot access element {} in a history of size {}"_format(index, Size()));
		}
		return history[(currentSlot + index) % Size()];
	}

	inline const SensorDataCollection& Get(int index) const {
		if (index < 0) {
			index += Size();
		}
		if (index < 0 || index >= Size()) {
			throw std::out_of_range("Cannot access element {} in a history of size {}"_format(index, Size()));
		}
		return history[(currentSlot + index) % Size()];
	}

	inline SensorDataCollection& operator[](int index) {
		return Get(index);
	}

	inline const SensorDataCollection& operator[](int index) const {
		return Get(index);
	}

	constexpr size_t Size() const noexcept {
		return N;
	}

	/**
	 * Advances the circular queue,
	 * returning the new slot to be filled.
	 */
	SensorDataCollection& NextSlot() noexcept {
		// Advance slot and wrap around if necessary
		currentSlot = (currentSlot + 1) % Size();
		return history[currentSlot];
	}

private:
	// The history data
	std::array<SensorDataCollection, N> history{};
	// The current slot (newest entry)
	size_t currentSlot = 0;
};


} // namespace opkey
