#pragma once


namespace OpKey {


class Sensor {
public:
	inline constexpr static const uint16_t KeyOffset = 0;
	inline constexpr static const uint16_t KeyCount = 88;
	inline constexpr static const uint16_t PedalOffset = 0;
	inline constexpr static const uint16_t PedalCount = 2;

public:
	Sensor() = default;

	Sensor(size_t index)
		: index(index)
	{
		if (index >= 90) {
			throw std::out_of_range("Sensor index must be in [0,90)");
		}
	}

	explicit operator size_t() const noexcept { return index; }

	bool IsPedal() const noexcept { return index >= 88; }
	size_t GetPedalIndex() const noexcept { return index - 88; }
	size_t GetKeyIndex() const noexcept { return index; }

private:
	size_t index = 0;
};


} // namespace OpKey
