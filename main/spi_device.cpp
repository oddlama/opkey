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
