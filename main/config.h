#pragma once

#include "sdkconfig.h"

#include <driver/gpio.h>
#include <driver/spi_master.h>

#include <array>


namespace opkey::config {


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
inline constexpr const size_t numChannels = 15;
inline constexpr const size_t DefaultMultisamples = 64;

/** Returns the sensor index for a given key index */
inline constexpr size_t GetSensorSwizzle(size_t keyIndex) {
	// Default correction:
	//    Sensor 0-87 = Key 87-0
	//    Sensor 88-89 = Pedal 1-2 (Key 88-89)
	if (keyIndex < 88) {
		return 87 - keyIndex;
	} else {
		return keyIndex;
	}
}

/**
 * The minimum coverage of the sensor range in percent requred
 * for a sensor to be considered functional.
 */
inline constexpr const double minimumSensorValueCoverage = 0.25;

/**
 * The minimum amount of usage cycles (significant key presses)
 * required for each sensor in the calibration phase.
 */
inline constexpr const uint16_t requiredCalibrationCycles = 8;

/**
 * The threshold which is used in the calibration phase to determine
 * if a sensor is close to its min or max boundary.
 * (in percent of the difference between min and max)
 */
inline constexpr const double calibrationNearBoundaryThreshold = 0.2;

/**
 * The minimum range covered before a travel between boundaries is
 * considered valid.
 */
inline constexpr const double calibrationNearBoundaryMinRange = 0.05;

} // namespace opkey::config
