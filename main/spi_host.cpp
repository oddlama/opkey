#include "spi_host.h"
#include "fmt.h"


namespace opkey {


SpiHost::SpiHost(std::string name, HostDevice hostDevice, gpio_num_t pinSclk, gpio_num_t pinMosi, gpio_num_t pinMiso, DmaChannel dmaChannel, int maxTransferSize)
	: initialized(true)
	, name(std::move(name))
	, pinSclk(pinSclk)
	, pinMosi(pinMosi)
	, pinMiso(pinMiso)
	, dmaChannel(dmaChannel)
{
	spi_bus_config_t busConfig{};
	busConfig.sclk_io_num     = pinSclk;
	busConfig.mosi_io_num     = pinMosi;
	busConfig.miso_io_num     = pinMiso;
	busConfig.quadwp_io_num   = GPIO_NUM_NC;
	busConfig.quadhd_io_num   = GPIO_NUM_NC;
	busConfig.max_transfer_sz = maxTransferSize;
    busConfig.flags           = (SPICOMMON_BUSFLAG_MASTER | SPICOMMON_BUSFLAG_SCLK | SPICOMMON_BUSFLAG_MOSI | SPICOMMON_BUSFLAG_MISO);
    busConfig.intr_flags      = 0;

	switch (hostDevice) {
		case HostDevice::None:
			throw std::runtime_error("Cannot initialize SpiHost with hostDevice=None");

		case HostDevice::Hspi: this->hostDevice = HSPI_HOST; break;
		case HostDevice::Vspi: this->hostDevice = VSPI_HOST; break;
	}

	esp::check(spi_bus_initialize(this->hostDevice, &busConfig, static_cast<int>(dmaChannel)), "spi_bus_initialize()");
	esp::logi("Initialized SpiHost{{name='{}', hostDevice={}, pinSclk={}, pinMosi={}, pinMiso={}}}"
		, this->name
		, hostDevice
		, static_cast<int>(pinSclk)
		, static_cast<int>(pinMosi)
		, static_cast<int>(pinMiso)
		);
}

SpiHost::~SpiHost() noexcept {
	if (initialized) {
		esp::check(spi_bus_free(hostDevice), "spi_bus_free()");
		esp::logi("Removed SpiHost{{name='{}', hostDevice={}}}", name, hostDevice);
	}
}


SpiHost::SpiHost(SpiHost&& other) noexcept
	: initialized(other.initialized)
	, hostDevice(other.hostDevice)
	, pinSclk(other.pinSclk)
	, pinMosi(other.pinMosi)
	, pinMiso(other.pinMiso)
	, dmaChannel(other.dmaChannel)
{
	other.initialized = false;
}

SpiHost& SpiHost::operator=(SpiHost&& other) noexcept {
	std::swap(initialized, other.initialized);
	std::swap(hostDevice, other.hostDevice);
	std::swap(pinSclk, other.pinSclk);
	std::swap(pinMosi, other.pinMosi);
	std::swap(pinMiso, other.pinMiso);
	std::swap(dmaChannel, other.dmaChannel);
	return *this;
}


SpiDevice SpiHost::AddDevice(std::string devName, gpio_num_t pinCs, int clockSpeedHz, int queueSize) {
	assert(initialized);
	spi_device_handle_t deviceHandle = nullptr;

	spi_device_interface_config_t devConfig{};
	devConfig.address_bits     = 0;
	devConfig.command_bits     = 0;
	devConfig.dummy_bits       = 0;
	devConfig.mode             = 0;
	devConfig.duty_cycle_pos   = 0;
	devConfig.cs_ena_posttrans = 0;
	devConfig.cs_ena_pretrans  = 0;
	devConfig.clock_speed_hz   = clockSpeedHz;
	devConfig.spics_io_num     = pinCs;
	devConfig.flags            = SPI_DEVICE_NO_DUMMY;
	devConfig.queue_size       = queueSize;
	devConfig.pre_cb           = nullptr;
	devConfig.post_cb          = nullptr;

	esp::check(spi_bus_add_device(hostDevice, &devConfig, &deviceHandle), "spi_bus_add_device(SpiHost{{name='{}'}})", name);
	return SpiDevice{std::move(devName), std::move(deviceHandle)};
}


} // namespace opkey
