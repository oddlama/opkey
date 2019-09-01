#pragma once

#include "entt.h"
#include "config.h"
#include "spi_host.h"
#include "spi_device.h"
#include "sensor_tensor.h"
#include "ads7953.h"


namespace opkey {


class AdcController {
public:
	AdcController();

	AdcController(const AdcController&) = default;
	AdcController(AdcController&&) = default;
	AdcController& operator=(const AdcController&) = delete;
	AdcController& operator=(AdcController&&) = delete;

	template<typename F>
	inline void Read(F&& callback) {
		OPKEY_PROFILE_FUNCTION();

		for (int a = 0; a < config::NumAdcs; ++a) {
			auto busGuard = adcs[a].AcquireBus();
			for (int c = 0; c < config::NumChannels; ++c) {
				adcs[a].TransferPolling(continueOperationTransactions[a * config::NumChannels + c]);
			}
		}

		for (int a = 0; a < config::NumAdcs; ++a) {
			for (int c = 0; c < config::NumChannels; ++c) {
				auto& rx = (*continueOperationRxs)[a * config::NumChannels + c];
				callback(a * config::NumChannels + rx.GetChannel(), rx.GetValue());
			}
		}
	}

	void Read(RawSensorData& data);
	void Read(SensorData& data, uint32_t samples);

private:
	void InitSpi();
	void InitAdcs();

private:
	// Spi
	SpiHost hspi{};
	SpiHost vspi{};
	std::array<SpiDevice, config::NumAdcs> adcs{};

	// Transactions and DMA buffers
	unique_ptr_dma<ads7953::Command> continueOperationTx
		= make_unique_dma<ads7953::Command>();
	unique_ptr_dma<std::array<ads7953::Result, config::NumAdcs * config::NumChannels>> continueOperationRxs
		= make_unique_dma<std::array<ads7953::Result, config::NumAdcs * config::NumChannels>>();
	std::array<spi_transaction_t, config::NumAdcs * config::NumChannels> continueOperationTransactions{};
};


} // namespace opkey
