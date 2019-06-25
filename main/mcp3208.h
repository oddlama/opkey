#pragma once

#include <array>

#include <SPI.h>


class Mcp3208 {
public:
	class Command {
	public:
		Command() noexcept = default;
		explicit Command(uint8_t channel, bool differential) noexcept {
			constexpr const uint8_t Start = 0x04;
			constexpr const uint8_t ModeSingle = 0x02;
			constexpr const uint8_t ModeDiff = 0x00;

			// Construct command 0b00000smc cc000000 (s=start, m=mode, c=channel)
			data[0] = Start | (differential ? ModeDiff : ModeSingle) | ((channel & 0x04) >> 2);
			data[1] = (channel & 0x03) << 6;
		}

		uint16_t Execute(SPI& spi) {
			printf("\n> %02x %02x %02x   ", data[0], data[1], data[2]);
			spi.transfer(data.data(), data.size());
			printf("< %02x %02x %02x    ", data[0], data[1] &0x0f, data[2]);
			return (static_cast<uint16_t>(data[1] & 0x0f) << 8) | data[2];
		}

	private:
		std::array<uint8_t, 3> data{};
	};

public:
	Mcp3208();
	uint16_t Read(Command command);
	uint16_t Read(uint8_t channel, bool differential = false);

private:
	SPI spi{};
};
