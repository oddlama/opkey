#pragma once

#include <driver/spi_master.h>

class SpiHost;

class SpiDevice {
	friend class SpiHost;

private:
	explicit SpiDevice(spi_device_handle_t&& handle);

public:
	SpiDevice() noexcept = default;
	~SpiDevice() noexcept;

	SpiDevice(const SpiDevice&) = delete;
	SpiDevice(SpiDevice&& other) noexcept = default;
	SpiDevice& operator=(const SpiDevice&) = delete;
	SpiDevice& operator=(SpiDevice&& other) noexcept = default;

	void Transfer(uint8_t* rxData, uint8_t* txData, size_t len);

private:
	spi_device_handle_t handle = nullptr;
};
