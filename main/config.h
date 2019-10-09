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

/** Returns the raw index for a given sensor index */
inline constexpr size_t GetRawIndexFromSensorIndex(size_t sensorIndex) {
	// Default correction:
	//    Key   87-0 = raw  0-87
	//    Pedal  0-1 = raw 88-89
	if (sensorIndex < 88) {
		return 87 - sensorIndex;
	} else {
		return sensorIndex;
	}
}

/** Returns the sensor index for a given raw index */
inline constexpr size_t GetSensorIndexFromRawIndex(size_t rawIndex) {
	// Function is reversible
	return GetRawIndexFromSensorIndex(rawIndex);
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
 * Single sensor history size for single sensor traces
 */
inline static constexpr const size_t singleSensorHistorySize = 7 * 4096u;

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

/**
 * The threshold below which the velocity must fall after
 * a maximum to trigger a keypress.
 */
inline constexpr const double triggerVelocityThreshold = 1.0;

/**
 * Maximum amount of time between velocity maximum and the trigger
 * that still counts as a keypress.
 */
inline constexpr const int64_t maxTriggerDelayUs = 40000;

/**
 * Mimumum amount of time between velocity maximum and the trigger.
 * This prevents key jitter from becoming keypresses.
 */
inline constexpr const int64_t minTriggerJitterDelayUs = 15000;

/**
 * Checks if a detected velocity maximum is valid and should
 * be considered a trigger candidate.
 */
inline constexpr const auto IsValidVelocityMaximum = [](double pos, double vel) {
		return vel >= 10.0 || (pos > .25 && vel > 3.0);
	};

/**
 * The distance relative to the press position a key has to
 * travel to be considered released.
 *
 * The relative part means, that if the key was pressed fully (1.0),
 * it needs to travel the given distance to be considered released.
 * If it was only pressed halfway (0.5), it only needs to travel half
 * of the given value to be considered released.
 */
inline constexpr const double releasePositionThreshold = 0.4;

/**
 * Keys with a position smaller than this value are always considered
 * released.
 */
inline constexpr const double releasePositionAbsolute = 0.15;

/** Maximum position to consider a pedal released */
inline constexpr const double pedalReleaseThreshold = 0.1;

/** Minimum position to consider a pedal pressed */
inline constexpr const double pedalPressThreshold = 0.2;

/**
 * The alpha factor of the exponential moving average (EMA)
 * calcuation for the key velocity.
 */
inline constexpr const double velocityEmaAlpha = 0.1;


// ================================================================
// Visualizer Config
// ================================================================

/**
 * The target fps for the visualizer.
 */
inline constexpr const double targetFps = 100.0;

/**
 * The target update time for the visualizer in microseconds.
 */
inline constexpr const int64_t targetUpdateTimeUs = static_cast<int64_t>(1000000.0 / targetFps);


} // namespace opkey::config
