#pragma once

#include <driver/spi_master.h>

class SpiHost;

class SpiDevice {
	friend class SpiHost;

private:
	explicit SpiDevice(spi_device_handle_t&& handle);

public:
	~SpiDevice() noexcept;

	SpiDevice(const SpiDevice&) = delete;
	SpiDevice(SpiDevice&& other) noexcept = default;
	SpiDevice& operator=(const SpiDevice&) = delete;
	SpiDevice& operator=(SpiDevice&& other) noexcept = default;

	void Transfer();

private:
	spi_device_handle_t handle = nullptr;
};
