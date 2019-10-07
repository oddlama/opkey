#pragma once

#include "config.h"
#include "ads7953.h"


namespace opkey {


class Sensor {
public:
	inline constexpr static const uint16_t keyOffset = 0;
	inline constexpr static const uint16_t keyCount = 88;
	inline constexpr static const uint16_t pedalOffset = keyCount;
	inline constexpr static const uint16_t pedalCount = 2;
	inline constexpr static const uint16_t totalCount = keyCount + pedalCount;

	inline constexpr static const uint16_t softPedal = pedalOffset + 0;
	inline constexpr static const uint16_t dampPedal = pedalOffset + 1;

public:
	Sensor() = default;

	Sensor(size_t index)
		: index(index)
	{
		if (index >= totalCount) {
			throw std::out_of_range("Sensor index must be in [0,totalCount)");
		}
	}

	explicit operator size_t() const noexcept { return index; }

	bool IsPedal() const noexcept { return index >= pedalOffset; }
	size_t GetIndex() const noexcept { return index; }
	size_t GetKeyIndex() const noexcept { return index; }
	size_t GetPedalIndex() const noexcept { return index - pedalOffset; }
	const char* GetName() const noexcept {
		static_assert(config::sensorNames.size() == totalCount, "config::sensorNames must have totalCount entries!");
		return config::sensorNames[index];
	}

	template<typename F>
	static inline void ForEach(F&& f) noexcept(noexcept(f(Sensor{}))) {
		Sensor s{};
		for (s.index = 0; s.index < totalCount; ++s.index) {
			f(s);
		}
	}

	template<typename F>
	static inline void ForEachKey(F&& f) noexcept(noexcept(f(Sensor{}))) {
		Sensor s{};
		for (s.index = keyOffset; s.index < keyOffset + keyCount; ++s.index) {
			f(s);
		}
	}

	template<typename F>
	static inline void ForEachPedal(F&& f) noexcept(noexcept(f(Sensor{}))) {
		Sensor s{};
		for (s.index = pedalOffset; s.index < pedalOffset + pedalCount; ++s.index) {
			f(s);
		}
	}

private:
	size_t index = 0;
};


} // namespace opkey
