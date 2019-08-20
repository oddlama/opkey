#pragma once

#include "config.h"
#include "profiler.h"
#include "fmt.h"
#include "sensor.h"
#include "sensor_tensor.h"

#include <esp_timer.h>

#include <stdexcept>
#include <memory>
#include <array>


namespace OpKey {


/**
 * A class to store the last N points of sensor data, and
 * the corresponding logical state
 */
template<size_t N>
class SensorHistory {
public:
	using History = std::array<SensorDataCollection, N>;

public:
	SensorHistory() = default;

	SensorHistory(const SensorHistory&) = default;
	SensorHistory(SensorHistory&&) = default;
	SensorHistory& operator=(const SensorHistory&) = delete;
	SensorHistory& operator=(SensorHistory&&) = delete;

	/**
	 * Initialize the history with the given valid data
	 */
	void Init(SensorData& newData) {
		OPKEY_PROFILE_FUNCTION();
		for (int i = 0; i < Size(); ++i) {
			Append(newData);
		}
	}

	/**
	 * Calculate and append a new data point to the history
	 */
	void Append(SensorData& newData) {
		OPKEY_PROFILE_FUNCTION();

		auto& t_0 = NextSlot();
		auto& t_1 = Get(-1); // Previous state

		auto now = esp_timer_get_time();
		t_0.timestamp = now;

		// Swizzle the raw data to match the sensor order
		for (size_t i = 0; i < newData.size(); ++i) {
			t_0.raw[i] = newData[Config::GetSensorSwizzle(i)];
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
			if (not t_1.keyState[i].pressed && t_0.kinematic.position[i] > 0.4 && t_0.kinematic.velocity[i] > 3.0) {
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
		return history->data()[(currentSlot + index) % Size()];
	}

	inline const SensorDataCollection& Get(int index) const {
		if (index < 0) {
			index += Size();
		}
		if (index < 0 || index >= Size()) {
			throw std::out_of_range("Cannot access element {} in a history of size {}"_format(index, Size()));
		}
		return history->data()[(currentSlot + index) % Size()];
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

private:
	/**
	 * Advances the circular queue,
	 * returning the new slot to be filled.
	 */
	SensorDataCollection& NextSlot() noexcept {
		// Advance slot and wrap around if necessary
		currentSlot = (currentSlot + 1) % Size();
		return history->data()[currentSlot];
	}

	// The history data
	std::unique_ptr<History> history = std::make_unique<History>();
	// The current slot (newest entry)
	size_t currentSlot = 0;
};


} // namespace OpKey
