#include "common.h"
#include "spi_device.h"

static const char* LOG_TAG = "OpKey.SpiDevice";

SpiDevice::SpiDevice(spi_device_handle_t&& handle)
	: handle(handle)
{
	esp::logi(LOG_TAG, "Initialized SpiDevice{{handle={}}}", static_cast<void*>(this->handle));
}

SpiDevice::~SpiDevice() noexcept {
	if (handle != nullptr) {
		ESP_ERROR_CHECK(spi_bus_remove_device(handle));
		esp::logi(LOG_TAG, "Removed SpiDevice{{handle={}}}", static_cast<void*>(handle));
	}
}

void SpiDevice::Transfer(uint8_t* rxData, uint8_t* txData, size_t len) {
	if (handle == nullptr) {
		throw std::runtime_error("Transfer() called on uninitialized SpiDevice");
	}

	spi_transaction_t transaction;
	transaction.flags     = 0;
	transaction.length    = len * 8;
	transaction.rxlength  = 0;
	transaction.tx_buffer = txData;
	transaction.rx_buffer = rxData;

	esp_err_t rc = spi_device_transmit(handle, &transaction);
	if (rc != ESP_OK) {
		esp::loge(LOG_TAG, "spi_device_transmit(handle={}) returned {}", static_cast<void*>(handle), rc);
	}
}
