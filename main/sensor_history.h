#pragma once

#include <esp_timer.h>

#include <stdexcept>
#include <memory>
#include <array>


namespace OpKey {


template<typename T>
using SensorTensor = std::array<T, 90>;


/**
 * A class to store the last N points of sensor data, and
 * the corresponding logical state
 */
template<size_t N>
class SensorHistory {
public:
	/**
	 * Raw sensor data.
	 */
	struct RawData {
		SensorTensor<uint16_t> value{};
	};

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

	struct LogicStateData {
		SensorTensor<LogicState> keyState;
	};

	struct Data {
		int64_t timestamp = -1;
		RawData raw{};
		KinematicData kinematic{};
		LogicStateData state{};

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

	// TODO void AppendRaw(*) {
	// TODO 	Data* slot = NextSlot();
	// TODO 	slot->timestamp = esp_timer_get_time();
	// TODO }

	/**
	 * Retrieves data from the history, with 0 denoting the newest
	 * history entry and size() - 1 the oldest.
	 */
	Data* Get(size_t index) {
		if (index >= Size()) {
			throw std::out_of_range("Cannot access element {} in a history of size {}"_format(index, Size()));
		}

		if (firstSlot + index >= history->data() + Size()) {
			return firstSlot + index - Size();
		} else {
			return firstSlot + index;
		}
	}

	/**
	 * Retrieves data from the history, with 0 denoting the newest
	 * history entry and size() - 1 the oldest.
	 */
	const Data* Get(size_t index) const {
		if (index >= Size()) {
			throw std::out_of_range("Cannot access element {} in a history of size {}"_format(index, Size()));
		}

		if (firstSlot + index >= history->data() + Size()) {
			return firstSlot + index - Size();
		} else {
			return firstSlot + index;
		}
	}

	constexpr size_t Size() const noexcept {
		return N;
	}

private:
	/**
	 * Advances the circular queue,
	 * returning the new slot to be filled.
	 */
	Data* NextSlot() noexcept {
		Data* slot = lastSlot;

		// Advance slot and wrap around if necessary
		++lastSlot;
		if (lastSlot >= history->data() + history->size()) {
			lastSlot = history->data();
		}

		firstSlot = slot;
		return slot;
	}

	// The history data
	std::unique_ptr<History> history = std::make_unique<History>();

	// The first slot (newest entry)
	Data* firstSlot = history->data();
	// The last slot (oldest entry, next acquired)
	Data* lastSlot = history->data();
};


} // namespace OpKey
