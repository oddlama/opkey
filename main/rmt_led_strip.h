#pragma once

#include "fmt.h"
#include "pixel.h"

#include <driver/rmt.h>
#include <driver/gpio.h>
#include <esp_err.h>

#include <array>
#include <stdexcept>

#include <cstdint>


namespace OpKey {


struct RmtTimings {
	inline constexpr const static uint64_t RmtBaseClock = APB_CLK_FREQ;
	inline constexpr const static uint8_t RmtClockDivider = 2;
	inline constexpr const static uint64_t RmtTicksPerSecond = (RmtBaseClock / RmtClockDivider);

	inline constexpr static uint64_t NsToTicks(uint32_t ns) {
		constexpr const uint64_t NsPerSecond = 1000000000;
		return ns * RmtTicksPerSecond / NsPerSecond;
	}
};


struct RmtValue {
	uint16_t valHigh = 0;
	uint16_t valLow = 0;
};


class RmtItem {
public:
	/**
	 * Initialize the item using high and low time in ns.
	 * Set the MSB of valHigh and clear the MSB of valLow,
	 * to set the signal levels.
	 */
	constexpr RmtItem(uint16_t nsHigh, uint16_t nsLow) noexcept
		: value
			{ static_cast<uint16_t>(RmtTimings::NsToTicks(nsHigh) | 0x8000)
			, static_cast<uint16_t>(RmtTimings::NsToTicks(nsLow) & 0x7fff)
			}
	{ }

	operator rmt_item32_t() const noexcept {
		return rmtItem;
	}

private:
	union {
		RmtValue value;
		rmt_item32_t rmtItem;
	};
};


struct RmtTimingsWs2812x : public RmtTimings {
    inline constexpr const static RmtItem RmtBit0 = RmtItem(400, 850);
    inline constexpr const static RmtItem RmtBit1 = RmtItem(800, 450);
    inline constexpr const static uint16_t RmtDurationReset = NsToTicks(300000);
};

struct RmtTimingsSk6812 : public RmtTimings {
    inline constexpr const static RmtItem RmtBit0 = RmtItem(400, 850);
    inline constexpr const static RmtItem RmtBit1 = RmtItem(800, 450);
    inline constexpr const static uint16_t RmtDurationReset = NsToTicks(80000);
};

struct RmtTimingsApa106 : public RmtTimings {
	inline constexpr const static RmtItem RmtBit0 = RmtItem(400, 1400);
	inline constexpr const static RmtItem RmtBit1 = RmtItem(1400, 400);
	inline constexpr const static uint16_t RmtDurationReset = NsToTicks(50000);
};


template<typename PixelType, typename TimingPolicy>
class RmtLedStrip {
public:
	RmtLedStrip(gpio_num_t pin, size_t pixelCount, rmt_channel_t rmtChannel = RMT_CHANNEL_0, int rmtMemBlockNum = 8)
		: rmtChannel(rmtChannel)
		, pixelCount(pixelCount)
	{
		esp::logi("Initialized RmtLedStrip{{pin={}, pixelCount={}, rmtChannel={}, rmtMemBlockNum={}}}", pin, pixelCount, rmtChannel, rmtMemBlockNum);
		editBuffer.resize(pixelCount);
		sendBuffer.resize(pixelCount);

		rmt_config_t config{};
		config.rmt_mode                  = RMT_MODE_TX;
		config.channel                   = this->rmtChannel;
		config.clk_div                   = TimingPolicy::RmtClockDivider;
		config.gpio_num                  = pin;
		config.mem_block_num             = rmtMemBlockNum;
		config.tx_config.loop_en         = false;
		config.tx_config.carrier_en      = false;
		config.tx_config.carrier_level   = RMT_CARRIER_LEVEL_LOW;
		config.tx_config.idle_output_en  = true;
		config.tx_config.idle_level      = RMT_IDLE_LEVEL_LOW;

		auto errRc = rmt_config(&config);
		if (errRc != ESP_OK) {
			esp::loge("rmt_config() returned {}", esp_err_to_name(errRc));
			throw std::runtime_error("rmt_config() returned {}"_format(esp_err_to_name(errRc)));
		}

		errRc = rmt_driver_install(this->rmtChannel, 0, 0);
		if (errRc != ESP_OK) {
			esp::loge("rmt_driver_install() returned {}", esp_err_to_name(errRc));
			throw std::runtime_error("rmt_driver_install() returned {}"_format(esp_err_to_name(errRc)));
		}

		errRc = rmt_translator_init(this->rmtChannel, RmtTranslate);
		if (errRc != ESP_OK) {
			esp::loge("rmt_translator_init() returned {}", esp_err_to_name(errRc));
			throw std::runtime_error("rmt_translator_init() returned {}"_format(esp_err_to_name(errRc)));
		}
	}

	RmtLedStrip(const RmtLedStrip&) noexcept = default;
	RmtLedStrip(RmtLedStrip&&) noexcept = default;
	RmtLedStrip& operator=(const RmtLedStrip&) = delete;
	RmtLedStrip& operator=(RmtLedStrip&&) = delete;

	~RmtLedStrip() noexcept {
		rmt_wait_tx_done(rmtChannel, 1000 / portTICK_PERIOD_MS);
		rmt_driver_uninstall(rmtChannel);
	}

	const PixelType& operator[](size_t i) const {
		if (i > pixelCount) {
			throw std::out_of_range("Cannot access pixel {} in a RmtLedStrip of {} pixels"_format(i, pixelCount));
		}
		return editBuffer[i];
	}

	PixelType& operator[](size_t i) {
		if (i > pixelCount) {
			throw std::out_of_range("Cannot access pixel {} in a RmtLedStrip of {} pixels"_format(i, pixelCount));
		}
		return editBuffer[i];
	}

	/**
	 * Checks if the rmt driver is idle (no pending transmission).
	 */
    bool CanUpdate() const noexcept {
        return rmt_wait_tx_done(rmtChannel, 0) == ESP_OK;
    }

	/**
	 * Updates the LED strip with the current pixel data.
	 */
	void Update(bool wait = false) {
		// Wait until previous transmission is completed
		if (auto err = rmt_wait_tx_done(rmtChannel, portMAX_DELAY); err != ESP_OK) {
			esp::logw("rmt_wait_tx_done() in RmtLedStrip::Update() returned {}", esp_err_to_name(err));
			return;
		}

		// "Swap" buffers (copy current state into send buffer)
		std::copy(editBuffer.begin(), editBuffer.end(), sendBuffer.begin());

		// Start transmitting the sending buffer, and only block until completion if wait is set.
		if (auto err = rmt_write_sample(rmtChannel, reinterpret_cast<const uint8_t*>(sendBuffer.data()), sendBuffer.size() * sizeof(PixelType), wait); err != ESP_OK) {
			esp::logw("rmt_write_sample() in RmtLedStrip::Update() returned {}", esp_err_to_name(err));
			return;
		}
	}

	void Clear() {
		for (auto& pixel : *this) {
			pixel.Clear();
		}
	}

	size_t Size() const noexcept { return pixelCount; }

	auto cbegin() const { return editBuffer.cbegin(); }
	auto begin() const { return editBuffer.begin(); }
	auto begin() { return editBuffer.begin(); }
	auto cend() const { return editBuffer.cend(); }
	auto end() const { return editBuffer.end(); }
	auto end() { return editBuffer.end(); }

private:
	static void IRAM_ATTR RmtTranslate
		( const void* src
		, rmt_item32_t* dest
		, size_t srcSize
		, size_t wantedNum
		, size_t* translatedSize
		, size_t* itemNum
	) {
		size_t size = 0;

		for (const uint8_t* curSrc = static_cast<const uint8_t*>(src); size * 8 < wantedNum; ++curSrc) {
			uint8_t data = *curSrc;

			for (uint8_t bit = 0; bit < 8; ++bit) {
				*dest = (data & 0x80) ? TimingPolicy::RmtBit1 : TimingPolicy::RmtBit0;
				++dest;
				data <<= 1;
			}
			++size;

			// The last byte needs a prolonged off-pulse, to include the reset time.
			if (size >= srcSize) {
				--dest;
				dest->duration1 = TimingPolicy::RmtDurationReset;
				break;
			}
		}

		*translatedSize = size;
		*itemNum = size * 8;
	}

private:
	rmt_channel_t rmtChannel;
	size_t pixelCount;

	std::vector<PixelType> editBuffer{};
	std::vector<PixelType> sendBuffer{};
};


} // namespace OpKey
