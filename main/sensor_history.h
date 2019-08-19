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
	/**
	 * Kinematic sensor data calculated from raw value and
	 * previous data points.
	 */
	struct KinematicData {
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

	using LogicStateData = SensorTensor<LogicState>;

	struct Data {
		int64_t timestamp = -1;
		SensorData raw{};
		KinematicData kinematic{};
		LogicStateData keyState{};

		/** Checks if this contains valid data */
		operator bool() const noexcept {
			return timestamp >= 0;
		}
	};

	using History = std::array<Data, N>;

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

		auto& slot = NextSlot();
		auto& t_1 = Get(-1); // Slot at t-1

		auto now = esp_timer_get_time();
		slot.timestamp = now;

		// Swizzle the raw data to match the sensor order
		for (size_t i = 0; i < newData.size(); ++i) {
			slot.raw[i] = newData[Config::GetSensorSwizzle(i)];
		}

		// Inverse delta time between now and t_1 in [1/s]
		double dt = 1000000.0 / (slot.timestamp - t_1.timestamp);

		for (size_t i = 0; i < newData.size(); ++i) {
			// Position is sqrt(data), because light intensity is 1/(distance^2)
			// TODO normalize data based on calibration
			// TODO position = sqrt(ApplyCalibration(newData[i], i));
			slot.kinematic.position[i] = sqrt(slot.raw[i]);
			slot.kinematic.velocity[i] = (slot.kinematic.position[i] - t_1.kinematic.position[i]) * dt;
			slot.kinematic.acceleration[i] = (slot.kinematic.velocity[i] - t_1.kinematic.velocity[i]) * dt;
			if (not t_1.keyState[i].pressed && slot.kinematic.position[i] > 0.3 && slot.kinematic.velocity[i] > 3.0) {
				slot.keyState[i].pressed = true;
			} else if (t_1.keyState[i].pressed && slot.kinematic.position[i] < 0.3) {
				slot.keyState[i].pressed = false;
			}
			slot.keyState[i].changed = slot.keyState[i].pressed != t_1.keyState[i].pressed;
			if (slot.keyState[i].changed) {
				if (slot.keyState[i].pressed) {
					slot.keyState[i].lastPressTime = now;
				} else {
					slot.keyState[i].lastReleaseTime = now;
				}
			}
		}
	}

	/**
	 * Retrieves data from the history, with 0 denoting the newest
	 * history entry and size() - 1 the second newest.
	 * Accessing negative elements is allowed. -1 will give the previous and (-size() + 1) the oldest
	 */
	inline Data& Get(int index) {
		if (index < 0) {
			index += Size();
		}
		if (index < 0 || index >= Size()) {
			throw std::out_of_range("Cannot access element {} in a history of size {}"_format(index, Size()));
		}

		if (firstSlot + index >= history->data() + Size()) {
			return *(firstSlot + index - Size());
		} else {
			return *(firstSlot + index);
		}
	}

	inline const Data& Get(int index) const {
		if (index < 0) {
			index += Size();
		}
		if (index < 0 || index >= Size()) {
			throw std::out_of_range("Cannot access element {} in a history of size {}"_format(index, Size()));
		}

		if (firstSlot + index >= history->data() + Size()) {
			return *(firstSlot + index - Size());
		} else {
			return *(firstSlot + index);
		}
	}

	inline Data& operator[](int index) {
		return Get(index);
	}

	inline const Data& operator[](int index) const {
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
	Data& NextSlot() noexcept {
		Data* slot = lastSlot;

		// Advance slot and wrap around if necessary
		++lastSlot;
		if (lastSlot >= history->data() + history->size()) {
			lastSlot = history->data();
		}

		firstSlot = slot;
		return *slot;
	}

	// The history data
	std::unique_ptr<History> history = std::make_unique<History>();

	// The first slot (newest entry)
	Data* firstSlot = history->data();
	// The last slot (oldest entry, next acquired)
	Data* lastSlot = history->data();
};


} // namespace OpKey
