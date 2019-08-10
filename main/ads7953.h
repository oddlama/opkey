#pragma once

#include <array>

#include "spi_device.h"


namespace OpKey::Ads7953 {


inline constexpr static const uint8_t NumChannels = 16;


struct CommandTag{};

struct alignas(4) Command {
	std::array<uint8_t, 2> data{};
};

struct alignas(4) Result {
	std::array<uint8_t, 2> data{};

	uint8_t GetChannel() const noexcept {
		return data[0] >> 4;
	};

	uint16_t GetValue() const noexcept {
		return (static_cast<uint16_t>(data[0] & 0b1111) << 8) | data[1];
	};
};

enum class InputRange {
	Half, // 0 to Vref
	Full, // 0 to 2xVref
};

struct SetModeManual : private CommandTag {
	// The next channel
	uint8_t nextChannel = 0;
	// Program settings (everything below)
	bool programSettings = false;
	// The input range
	InputRange inputRange = InputRange::Half;
	// Poweroff on 16th SCLK falling edge
	bool poweroff = false;
	// Enable GPIO control.
	// Instead of the currently selected analog input channel, the GPIO input
	// values will be returned, and gpioOutputData will be written for output
	// GPIO pins.
	bool gpioControl = false;
	// Data for GPIOs configured as output. Ignored if gpioControl is false.
	// Bits 0-3 correspond to GPIO channels 0-3.
	uint8_t gpioOutputData = 0;

	Command ToCommand() const noexcept {
		Command ret{};
		if (programSettings) {
			ret.data[0] = 0b00011000;
			ret.data[1] = (static_cast<uint8_t>(inputRange) << 6)
				| (static_cast<uint8_t>(poweroff) << 5)
				| (static_cast<uint8_t>(gpioControl) << 4)
				| (gpioOutputData & 0b1111);
		} else {
			ret.data[0] = 0b00010000;
		}
		return ret;
	}
};

struct SetModeAuto1 : private CommandTag {
	// Program settings (everything below)
	bool programSettings = false;
	// Reset channel counter to lowest programmed channel
	bool resetCounter = false;
	// The input range
	InputRange inputRange = InputRange::Half;
	// Poweroff on 16th SCLK falling edge
	bool poweroff = false;
	// Enable GPIO control.
	// Instead of the currently selected analog input channel, the GPIO input
	// values will be returned, and gpioOutputData will be written for output
	// GPIO pins.
	bool gpioControl = false;
	// Data for GPIOs configured as output. Ignored if gpioControl is false.
	// Bits 0-3 correspond to GPIO channels 0-3.
	uint8_t gpioOutputData = 0;

	Command ToCommand() const noexcept {
		Command ret{};
		if (programSettings) {
			ret.data[0] = 0b00101000;
			ret.data[1] = (static_cast<uint8_t>(inputRange) << 6)
				| (static_cast<uint8_t>(poweroff) << 5)
				| (static_cast<uint8_t>(gpioControl) << 4)
				| (gpioOutputData & 0b1111);
		} else {
			ret.data[0] = 0b00100000;
		}
		return ret;
	}
};

struct SetModeAuto2 : private CommandTag {
	// Program settings (everything below)
	bool programSettings = false;
	// Reset channel counter to channel 0
	bool resetCounter = false;
	// The input range
	InputRange inputRange = InputRange::Half;
	// Poweroff on 16th SCLK falling edge
	bool poweroff = false;
	// Enable GPIO control.
	// Instead of the currently selected analog input channel, the GPIO input
	// values will be returned, and gpioOutputData will be written for output
	// GPIO pins.
	bool gpioControl = false;
	// Data for GPIOs configured as output. Ignored if gpioControl is false.
	// Bits 0-3 correspond to GPIO channels 0-3.
	uint8_t gpioOutputData = 0;

	Command ToCommand() const noexcept {
		Command ret{};
		if (programSettings) {
			ret.data[0] = 0b00111000;
			ret.data[1] = (static_cast<uint8_t>(inputRange) << 6)
				| (static_cast<uint8_t>(poweroff) << 5)
				| (static_cast<uint8_t>(gpioControl) << 4)
				| (gpioOutputData & 0b1111);
		} else {
			ret.data[0] = 0b00110000;
		}
		return ret;
	}
};

struct ProgramModeAuto1 : private CommandTag {
	uint16_t channelMask = 0xffff;

	Command ToCommand() const noexcept {
		Command ret{};
		ret.data[0] = 0b10000000;
		return ret;
	}

	Command AuxCommand() const noexcept {
		Command ret{};
		ret.data[0] = static_cast<uint8_t>(channelMask >> 8);
		ret.data[1] = static_cast<uint8_t>(channelMask & 0xff);
		return ret;
	}
};

struct ProgramModeAuto2 : private CommandTag {
	uint8_t lastChannel = 0x0f;

	Command ToCommand() const noexcept {
		Command ret{};
		ret.data[0] = 0b10010000 | (lastChannel >> 2);
		ret.data[1] = (lastChannel << 6);
		return ret;
	}
};

struct ContinueOperation : private CommandTag {
	Command ToCommand() const noexcept {
		return Command{};
	}
};


template<typename T>
inline void Transfer(SpiDevice& device, Result& rxBuf, Command& txBuf, T& command) {
	txBuf = command.ToCommand();
	device.Transfer(rxBuf.data.data(), rxBuf.data.size(), txBuf.data.data(), txBuf.data.size());
}

inline void Transfer(SpiDevice& device, Result& rxBuf, Command& txBuf, ProgramModeAuto1& command) {
	txBuf = command.ToCommand();
	device.Transfer(rxBuf.data.data(), rxBuf.data.size(), txBuf.data.data(), txBuf.data.size());
	txBuf = command.AuxCommand();
	device.Transfer(rxBuf.data.data(), rxBuf.data.size(), txBuf.data.data(), txBuf.data.size());
}


} // namespace OpKey::Ads7953
