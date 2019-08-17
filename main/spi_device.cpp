#include "spi_device.h"
#include "fmt.h"


namespace OpKey {


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


void SpiDevice::Transfer(uint8_t* rxData, size_t rxLen, uint8_t* txData, size_t txLen) {
	if (handle == nullptr) {
		throw std::runtime_error("Transfer() called on uninitialized SpiDevice");
	}

	spi_transaction_t transaction;
	transaction.flags     = 0;
	transaction.length    = txLen * 8;
	transaction.rxlength  = rxLen * 8;
	transaction.tx_buffer = txData;
	transaction.rx_buffer = rxData;

	esp_err_t rc = spi_device_transmit(handle, &transaction);
	if (rc != ESP_OK) {
		esp::loge("spi_device_transmit(SpiDevice{{name='{}'}}) returned {}", name, rc);
	}
}


} // namespace OpKey
