#pragma once


namespace OpKey {


class Sensor {
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

private:
	size_t index = 0;
};


} // namespace OpKey
