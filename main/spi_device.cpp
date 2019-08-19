#include "profiler.h"
#include "spi_device.h"
#include "fmt.h"


namespace OpKey {


SpiDevice::AcquireGuard::AcquireGuard(SpiDevice& spiDevice)
	: spiDevice(spiDevice)
{
	if (auto rc = spi_device_acquire_bus(spiDevice.handle, portMAX_DELAY); rc != ESP_OK) {
		esp::loge("spi_device_acquire_bus(SpiDevice{{name='{}'}}) returned {}", spiDevice.name, esp_err_to_name(rc));
		throw std::runtime_error("spi_device_acquire_bus(SpiHost{{name='{}'}}) returned {}"_format(spiDevice.name, esp_err_to_name(rc)));
	}
}

SpiDevice::AcquireGuard::~AcquireGuard() noexcept {
	spi_device_release_bus(spiDevice.handle);
}


SpiDevice::SpiDevice(std::string name, spi_device_handle_t&& handle)
	: handle(handle)
	, name(std::move(name))
{
	esp::logi("Initialized SpiDevice{{name='{}'}}", this->name);
}

SpiDevice::~SpiDevice() noexcept {
	if (handle != nullptr) {
		ESP_ERROR_CHECK(spi_bus_remove_device(handle));
		esp::logi("Removed SpiDevice{{name='{}'}}", name);
	}
}


SpiDevice::SpiDevice(SpiDevice&& other) noexcept
	: handle(other.handle)
	, name(std::move(other.name))
{
	other.handle = nullptr;
}

SpiDevice& SpiDevice::operator=(SpiDevice&& other) noexcept {
	std::swap(handle, other.handle);
	std::swap(name, other.name);
	return *this;
}


} // namespace OpKey
