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

inline constexpr const int spiFrequency = SPI_MASTER_FREQ_10M / 2;


// ================================================================
// Adc Config
// ================================================================

inline constexpr const int numAdcs = 6;
inline constexpr const size_t numChannels = 15;
inline constexpr const size_t defaultMultisamples = 64;

/** Returns the sensor index for a given raw sensor index */
inline constexpr size_t GetSensorSwizzle(size_t rawIndex) {
	// Default correction:
	//    raw 0-87 = Key 87-0
	//    raw 88-89 = Pedal 0-1
	if (rawIndex < 88) {
		return 87 - rawIndex;
	} else {
		return rawIndex;
	}
}

/** Returns the raw index for a given sensor */
inline constexpr size_t GetSensorSwizzleReverse(size_t sensorIndex) {
	// Currently the function is reversible
	return GetSensorSwizzle(sensorIndex);
}

// ================================================================
// Calibration Config
// ================================================================

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
inline constexpr const double calibrationNearBoundaryThreshold = 0.25;

/**
 * The minimum range covered before a travel between boundaries is
 * considered valid.
 */
inline constexpr const double calibrationNearBoundaryMinRange = 0.05;


// ================================================================
// Sensor Config
// ================================================================

/**
 * Names for the sensors. Max 4 characters!
 */
inline constexpr const std::array<const char*, 90> sensorNames =
	{ "A0", "A#0", "B0"
	, "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1"
	, "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2"
	, "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3"
	, "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4"
	, "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5"
	, "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6"
	, "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7"
	, "C8"
	, "Soft", "Damp"
	};

inline constexpr const double posLowThreshold = 0.15;
inline constexpr const double posControlThreshold = 0.25;
inline constexpr const double posHighThreshold = 0.32;

/**
 * The minimum amout of time (in us) that must have passed before any
 * of the thresholds can be triggered again. This is to prevent jitter,
 * noise and other "quick succession" triggers to influence the calculation.
 *
 * For reference: A cycle for a quick staccato-keypress lasts for around 60ms to 120ms.
 */
inline constexpr const int64_t posThresholdJitterDelayUs = 5000;


} // namespace opkey::config
