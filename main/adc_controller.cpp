#include "adc_controller.h"
#include "application.h"
#include "ads7953.h"
#include "fmt.h"
#include "exception.h"


namespace opkey {


AdcController::AdcController() {
	OPKEY_PROFILE_FUNCTION();
	InitSpi();
}


void AdcController::InitSpi() {
	OPKEY_PROFILE_FUNCTION();
	esp::logi("Initializing SPI");

	hspi = SpiHost
		{ "hspi"
		, SpiHost::HostDevice::Hspi
		, config::hspi.pinSclk
		, config::hspi.pinMosi
		, config::hspi.pinMiso
		, DmaChannel::Dma1
		, 16
		};

	vspi = SpiHost
		{ "vspi"
		, SpiHost::HostDevice::Vspi
		, config::vspi.pinSclk
		, config::vspi.pinMosi
		, config::vspi.pinMiso
		, DmaChannel::Dma2
		, 16
		};

	adcs =
		{ hspi.AddDevice("adc0", config::hspi.pinCs[0], config::spiFrequency)
		, hspi.AddDevice("adc1", config::hspi.pinCs[1], config::spiFrequency)
		, hspi.AddDevice("adc2", config::hspi.pinCs[2], config::spiFrequency)
		, vspi.AddDevice("adc3", config::vspi.pinCs[0], config::spiFrequency)
		, vspi.AddDevice("adc4", config::vspi.pinCs[1], config::spiFrequency)
		, vspi.AddDevice("adc5", config::vspi.pinCs[2], config::spiFrequency)
		};
}

void AdcController::SetAdcModeAuto() {
	OPKEY_PROFILE_FUNCTION();
	esp::logi("Set mode auto for ADCs");

	// Set mode to Auto1 with full input range
	auto setModeAuto1 = ads7953::SetModeAuto1{};
	setModeAuto1.programSettings = true;
	setModeAuto1.inputRange = ads7953::InputRange::Full;

	// Disable reading CH15
	auto programModeAuto1 = ads7953::ProgramModeAuto1{};
	programModeAuto1.channelMask = 0x7fff;

	auto tx = make_unique_dma<ads7953::Command>();
	auto rx = make_unique_dma<ads7953::Result>();
	for (auto& adc : adcs) {
		esp::logi("Set mode for '{}'", adc.GetName());
		ads7953::Transfer(adc, *rx, *tx, setModeAuto1);
		esp::logi("{:08b} {:08b}", rx->data[0], rx->data[1]);
		ads7953::Transfer(adc, *rx, *tx, programModeAuto1);
		esp::logi("{:08b} {:08b}", rx->data[0], rx->data[1]);
	}

	// Prepare several continueOperation transactions linked to rx and tx,
	// preinitialized with ads7953::ContinueOperation
	auto continueOperation = ads7953::ContinueOperation{};
	*continueOperationTx = continueOperation.ToCommand();

	for (int i = 0; i < config::numAdcs * config::numChannels; ++i) {
		continueOperationTransactions[i].flags     = 0;
		continueOperationTransactions[i].length    = continueOperationTx->data.size() * 8;
		continueOperationTransactions[i].tx_buffer = continueOperationTx->data.data();
		continueOperationTransactions[i].rxlength  = (*continueOperationRxs)[i].data.size() * 8;
		continueOperationTransactions[i].rx_buffer = (*continueOperationRxs)[i].data.data();
	}

	// Check that every adc is online and correctly
	// programmed by verifying a two full cycles
	for (auto& adc : adcs) {
		ads7953::Transfer(adc, *rx, *tx, continueOperation);
		int channel = rx->GetChannel();
		for (int i = 0; i < 2 * 15; ++i) {
			int expectedChannel = (channel + 1) % 15;
			ads7953::Transfer(adc, *rx, *tx, continueOperation);
			if (rx->GetChannel() != expectedChannel) {
				throw OpKeyException("ADC mode set error: '{}' returned invalid data"_format(adc.GetName()));
			}
			channel = expectedChannel;
		}
	}
}

void AdcController::SetAdcModeSingle() {
	OPKEY_PROFILE_FUNCTION();
	esp::logi("Set mode single channel auto for ADCs");

	// Set mode to Auto1 with full input range
	auto setModeAuto1 = ads7953::SetModeAuto1{};
	setModeAuto1.programSettings = true;
	setModeAuto1.inputRange = ads7953::InputRange::Full;

	// Disable reading all channels except the configured one
	int sChannel = config::GetRawIndexFromSensorIndex(mode_params::singleSensorMonitoringSensor.GetIndex()) % config::numChannels;
	auto programModeAuto1 = ads7953::ProgramModeAuto1{};
	programModeAuto1.channelMask = 1 << sChannel;

	auto tx = make_unique_dma<ads7953::Command>();
	auto rx = make_unique_dma<ads7953::Result>();
	for (int a = 0; a < config::numAdcs; ++a) {
		auto& adc = adcs[a];

		esp::logi("Set mode for '{}'", adc.GetName());
		ads7953::Transfer(adc, *rx, *tx, setModeAuto1);
		esp::logi("{:08b} {:08b}", rx->data[0], rx->data[1]);
		ads7953::Transfer(adc, *rx, *tx, programModeAuto1);
		esp::logi("{:08b} {:08b}", rx->data[0], rx->data[1]);
	}

	// Prepare several continueOperation transactions linked to rx and tx,
	// preinitialized with ads7953::ContinueOperation
	auto continueOperation = ads7953::ContinueOperation{};
	*continueOperationTx = continueOperation.ToCommand();

	for (int i = 0; i < config::numAdcs * config::numChannels; ++i) {
		continueOperationTransactions[i].flags     = 0;
		continueOperationTransactions[i].length    = continueOperationTx->data.size() * 8;
		continueOperationTransactions[i].tx_buffer = continueOperationTx->data.data();
		continueOperationTransactions[i].rxlength  = (*continueOperationRxs)[i].data.size() * 8;
		continueOperationTransactions[i].rx_buffer = (*continueOperationRxs)[i].data.data();
	}

	// Check that every adc is online and correctly
	// programmed by verifying a two full cycles
	for (auto& adc : adcs) {
		// Discard next operation, as it will be invalid (old conversion result and channel)
		ads7953::Transfer(adc, *rx, *tx, continueOperation);
		for (int i = 0; i < 2 * 15; ++i) {
			ads7953::Transfer(adc, *rx, *tx, continueOperation);
			if (rx->GetChannel() != sChannel) {
				throw OpKeyException("ADC mode set error: '{}' returned invalid data"_format(adc.GetName()));
			}
		}
	}
}


} // namespace opkey
