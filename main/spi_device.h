#pragma once

#include <driver/spi_master.h>
#include <string>


namespace OpKey {


class SpiHost;

class SpiDevice {
	friend class SpiHost;

private:
	explicit SpiDevice(std::string name, spi_device_handle_t&& handle);

public:
	SpiDevice() noexcept = default;
	~SpiDevice() noexcept;

	SpiDevice(SpiDevice&& other) noexcept;
	SpiDevice& operator=(SpiDevice&& other) noexcept;

	SpiDevice(const SpiDevice&) = delete;
	SpiDevice& operator=(const SpiDevice&) = delete;

	const std::string& GetName() const noexcept { return name; }

	void Transfer(uint8_t* rxData, size_t rxLen, uint8_t* txData, size_t txLen);

private:
	spi_device_handle_t handle = nullptr;
	std::string name{};
};


} // namespace OpKey
