#pragma once

#include "dma.h"
#include "spi_device.h"

#include <driver/spi_master.h>
#include <driver/gpio.h>
#include <string>


namespace OpKey {


class SpiHost {
public:
	enum class HostDevice {
		None,
		Hspi,
		Vspi,
	};

public:
	explicit SpiHost() noexcept = default;
	explicit SpiHost(std::string name, HostDevice hostDevice, gpio_num_t pinSclk, gpio_num_t pinMosi, gpio_num_t pinMiso, DmaChannel dmaChannel);
	~SpiHost() noexcept;

	SpiHost(SpiHost&& other) noexcept;
	SpiHost& operator=(SpiHost&& other) noexcept;

	SpiHost(const SpiHost&) = delete;
	SpiHost& operator=(const SpiHost&) = delete;

	SpiDevice AddDevice(std::string devName, gpio_num_t pinCs, int clockSpeedHz, int queueSize = 64);

	const std::string& GetName() const noexcept { return name; }

private:
	bool initialized = false;

	spi_host_device_t hostDevice{};
	std::string name{};
	gpio_num_t pinSclk = GPIO_NUM_NC;
	gpio_num_t pinMosi = GPIO_NUM_NC;
	gpio_num_t pinMiso = GPIO_NUM_NC;
	DmaChannel dmaChannel = DmaChannel::None;
};


} // namespace OpKey
