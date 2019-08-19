#pragma once

#include "entt.h"
#include "config.h"
#include "spi_host.h"
#include "spi_device.h"
#include "sensor_tensor.h"
#include "ads7953.h"


namespace OpKey {


class AdcController {
public:
	AdcController();

	AdcController(const AdcController&) = default;
	AdcController(AdcController&&) = default;
	AdcController& operator=(const AdcController&) = delete;
	AdcController& operator=(AdcController&&) = delete;

	void Read(RawSensorData& data);
	void Read(RawSensorData& data, uint32_t samples);

private:
	void InitSpi();
	void InitAdcs();

private:
	// Spi
	SpiHost hspi{};
	SpiHost vspi{};
	std::array<SpiDevice, Config::NumAdcs> adcs{};

	// Transactions and DMA buffers
	unique_ptr_dma<Ads7953::Command> continueOperationTx = make_unique_dma<Ads7953::Command>();
	unique_ptr_dma<std::array<Ads7953::Result, 15*6>> continueOperationRxs = make_unique_dma<std::array<Ads7953::Result, 15*6>>();
	std::array<spi_transaction_t, 15*6> continueOperationTransactions{};
};


} // namespace OpKey
