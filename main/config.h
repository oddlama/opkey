#pragma once

#include "sdkconfig.h"

#include <driver/gpio.h>
#include <driver/spi_master.h>

#include <array>


namespace OpKey::Config {


struct SpiConfig {
	const gpio_num_t pinMiso;
	const gpio_num_t pinMosi;
	const gpio_num_t pinSclk;
	const std::array<gpio_num_t, 3> pinCs;
};

enum class ChannelFunction {
	// 0x00-0x7f reserved for keys
	PedalSustain  = 0xfd,
	PedalUnaCorda = 0xfe,
	None          = 0xff,
};


// ================================================================
// General Config
// ================================================================

inline constexpr const uint8_t MainCore = 1;
inline constexpr const uint8_t VisualizerCore = 0;


// ================================================================
// Spi Config
// ================================================================

inline constexpr const SpiConfig hspi =
	{ GPIO_NUM_12
	, GPIO_NUM_13
	, GPIO_NUM_14
	, { GPIO_NUM_15
	  , GPIO_NUM_16
	  , GPIO_NUM_17
	  }
	};

inline constexpr const SpiConfig vspi =
	{ GPIO_NUM_19
	, GPIO_NUM_23
	, GPIO_NUM_18
	, { GPIO_NUM_5
	  , GPIO_NUM_25
	  , GPIO_NUM_26
	  }
	};

inline constexpr const int SpiFrequency = SPI_MASTER_FREQ_10M / 2;


// ================================================================
// Adc Config
// ================================================================

inline constexpr const int NumAdcs = 6;
inline constexpr const size_t NumChannels = 15;
inline constexpr const size_t DefaultMultisamples = 64;

//Map(adcs, hspi, hspi.pinCs[0], {
//	}
// Maps each adc's channel to a key, or 255 for unused.[adcIndex * Ads7953::NumChannels + channelIndex] -> keyIndex [0-87]
//inline constexpr const std::array<uint8_t, > ChannelFunctions = 6;
//inline constexpr const std::array<uint8_t, > MidiAdcChannelToKey = 6;
//
//inline constexpr uint8_t KeyNumberToMidiNote(uint8_t key) {
//	// MIDI 21 = A0
//	return 21 + key;
//}


} // namespace OpKey::Config
