#pragma once

#include <esp_timer.h>

#include <array>
#include <utility>


namespace opkey::midi {

namespace status {

constexpr const uint8_t controlChange = 0xb0;
constexpr const uint8_t noteOn = 0x90;
constexpr const uint8_t noteOff = 0x80;

} // namespace status

constexpr const uint8_t ccSensorSoft = 0x43;
constexpr const uint8_t ccSensorDamp = 0x40;


inline std::pair<uint8_t, uint8_t> Header() noexcept {
	// Extract 17 bits of millis
	uint32_t millis = 0x1fff & static_cast<uint32_t>(esp_timer_get_time() / 1000);
	return
		{ 0x80 | (millis >> 7)   // MSB | 6 highest bits of timestamp
		, 0x80 | (millis & 0x7f) // MSB | 7 lowest bits of timestamp
		};
}


} // namespace opkey::midi
