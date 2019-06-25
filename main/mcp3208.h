#pragma once

#include <array>

#include <SPI.h>


class Mcp3208 {
public:
	class Command {
	public:
		Command() noexcept = default;
		explicit inline Command(uint8_t channel, bool differential) noexcept {
			constexpr const uint8_t Start = 0x04;
			constexpr const uint8_t ModeSingle = 0x02;
			constexpr const uint8_t ModeDiff = 0x00;

			// Construct command 0b00000smc cc000000 (s=start, m=mode, c=channel)
			data[0] = Start | (differential ? ModeDiff : ModeSingle) | ((channel & 0x04) >> 2);
			data[1] = (channel & 0x03) << 6;
		}

		inline uint16_t GetValue() const noexcept {
			return (static_cast<uint16_t>(data[1] & 0x0f) << 8) | data[2];
		}

		inline void Execute(Mcp3208& mcp) {
			mcp.spi.transfer(data.data(), data.size());
		}

		static inline void Execute(Mcp3208& mcp, Command* commands, size_t count) {
			mcp.spi.transfer(commands[0].data.data(), count * commands[0].data.size());
		}

	private:
		// Use 4 bytes of data for DMA alignment
		std::array<uint8_t, 4> data{};
	};

	friend class Command;

public:
	Mcp3208();
	inline uint16_t Read(uint8_t channel, bool differential = false);

private:
	SPI spi{};
};
