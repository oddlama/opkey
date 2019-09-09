#pragma once

#include "entt.h"
#include "config.h"
#include "spi_host.h"
#include "spi_device.h"
#include "sensor_tensor.h"
#include "ads7953.h"
#include "mode.h"


namespace opkey {


class AdcController {
public:
	AdcController();

	AdcController(const AdcController&) = default;
	AdcController(AdcController&&) = default;
	AdcController& operator=(const AdcController&) = delete;
	AdcController& operator=(AdcController&&) = delete;

	inline void ReadSingle(uint16_t* data, size_t count) {
		OPKEY_PROFILE_FUNCTION();

		int adcIndex = config::GetSensorSwizzleReverse(mode_params::singleSensorMonitoringSensor.GetIndex()) / config::numChannels;
		auto& adc = adcs[adcIndex];
		auto busGuard = adc.AcquireBus();
		for (size_t i = 0; i < count; ++i) {
			adc.TransferPolling(continueOperationTransactions[0]);
			data[i] = (*continueOperationRxs)[0].GetValue();
		}
	}

	template<typename F>
	inline void Read(F&& callback) {
		OPKEY_PROFILE_FUNCTION();

		for (int a = 0; a < config::numAdcs; ++a) {
			auto busGuard = adcs[a].AcquireBus();
			for (int c = 0; c < config::numChannels; ++c) {
				adcs[a].TransferPolling(continueOperationTransactions[a * config::numChannels + c]);
			}
		}

		for (int a = 0; a < config::numAdcs; ++a) {
			for (int c = 0; c < config::numChannels; ++c) {
				auto& rx = (*continueOperationRxs)[a * config::numChannels + c];
				callback(a * config::numChannels + rx.GetChannel(), rx.GetValue());
			}
		}
	}

	void Read(RawSensorData& data);
	void Read(SensorData& data, uint32_t samples);

	void SetAdcModeAuto();
	void SetAdcModeSingle();

private:
	void InitSpi();

private:
	// Spi
	SpiHost hspi{};
	SpiHost vspi{};
	std::array<SpiDevice, config::numAdcs> adcs{};

	// Transactions and DMA buffers
	unique_ptr_dma<ads7953::Command> continueOperationTx
		= make_unique_dma<ads7953::Command>();
	unique_ptr_dma<std::array<ads7953::Result, config::numAdcs * config::numChannels>> continueOperationRxs
		= make_unique_dma<std::array<ads7953::Result, config::numAdcs * config::numChannels>>();
	std::array<spi_transaction_t, config::numAdcs * config::numChannels> continueOperationTransactions{};
};


} // namespace opkey
