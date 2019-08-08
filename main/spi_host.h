#pragma once

#include <driver/spi_master.h>
#include "spi_device.h"


class SpiHost {
public:
	enum class HostDevice {
		None,
		Hspi,
		Vspi,
	};

	enum class DmaChannel {
		None = 0,
		Dma1 = 1,
		Dma2 = 2,
	};

public:
	explicit SpiHost() noexcept = default;
	explicit SpiHost(HostDevice hostDevice, gpio_num_t pinSclk, gpio_num_t pinMosi, gpio_num_t pinMiso, DmaChannel dmaChannel);
	~SpiHost() noexcept;

	SpiHost(SpiHost&& other) noexcept;
	SpiHost& operator=(SpiHost&& other) noexcept;

	SpiHost(const SpiHost&) = delete;
	SpiHost& operator=(const SpiHost&) = delete;

	SpiDevice AddDevice(gpio_num_t pinCs, int clockSpeedHz, int queueSize = 64);

private:
	bool initialized = false;

	spi_host_device_t hostDevice{};
	gpio_num_t pinSclk = GPIO_NUM_NC;
	gpio_num_t pinMosi = GPIO_NUM_NC;
	gpio_num_t pinMiso = GPIO_NUM_NC;
	DmaChannel dmaChannel = DmaChannel::None;
};
