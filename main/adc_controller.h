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

	inline void ReadSingle(uint16_t* data, size_t count, int64_t delayUs = 0) {
		OPKEY_PROFILE_FUNCTION();

		int adcIndex = config::GetRawIndexFromSensorIndex(mode_params::singleSensorMonitoringSensor.GetIndex()) / config::numChannels;
		auto& adc = adcs[adcIndex];
		auto busGuard = adc.AcquireBus();
		for (size_t i = 0; i < count; ++i) {
			auto b = esp_timer_get_time();
			adc.TransferPolling(continueOperationTransactions[0]);
			data[i] = (*continueOperationRxs)[0].GetValue();
			while (esp_timer_get_time() - b < delayUs) {
				; // wait
			}
		}
	}

	template<typename F>
	inline void ReadRaw(F&& callback) {
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

	template<typename F>
	inline void Read(F&& callback) {
		OPKEY_PROFILE_FUNCTION();

		int prevA = 0;
		int i = 0;

		auto ProcessPrevious = [&]() {
			auto& prevRx = (*continueOperationRxs)[i - 1];
			callback(prevA * config::numChannels + prevRx.GetChannel(), double(prevRx.GetValue()) / ads7953::values);
		};

		for (int a = 0; a < config::numAdcs; ++a) {
			auto busGuard = adcs[a].AcquireBus();
			for (int c = 0; c < config::numChannels; ++c, ++i) {
				adcs[a].PollingStart(continueOperationTransactions[i]);
				// While the SPI peripheral transmits this transaction, we will process
				// the previous result
				if (i > 0) {
					ProcessPrevious();
				}
				prevA = a;
				adcs[a].PollingEnd();
			}
		}

		// Process the last one
		ProcessPrevious();
	}

	inline void Read(RawSensorData& data) {
		OPKEY_PROFILE_FUNCTION();

		ReadRaw([&](auto i, auto val) {
				data[i] = val;
			});
	}

	inline void Read(SensorData& data, uint32_t samples) {
		OPKEY_PROFILE_FUNCTION();

		data = SensorData{};
		auto Accumulate = [&](auto i, auto val) {
				data[i] += double(val) / (samples * ads7953::values);
			};

		for (int s = 0; s < samples; ++s) {
			Read(Accumulate);
		}
	}

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
