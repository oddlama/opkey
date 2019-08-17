#include "adc_controller.h"
#include "application.h"
#include "ads7953.h"
#include "fmt.h"
#include "exception.h"


namespace OpKey {


#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#define PROFILE_SCOPE(name) auto MACRO_CONCAT(automaticProfilerGuard_, __COUNTER__) = application.GetProfiler()(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)


AdcController::AdcController(Application& application)
	: application(application)
{
	PROFILE_FUNCTION();
	InitSpi();
	InitAdcs();
}


void AdcController::InitSpi() {
	PROFILE_FUNCTION();
	esp::logi("Initializing SPI");

	hspi = SpiHost
		{ "hspi"
		, SpiHost::HostDevice::Hspi
		, Config::hspi.pinSclk
		, Config::hspi.pinMosi
		, Config::hspi.pinMiso
		, DmaChannel::Dma1
		};

	vspi = SpiHost
		{ "vspi"
		, SpiHost::HostDevice::Vspi
		, Config::vspi.pinSclk
		, Config::vspi.pinMosi
		, Config::vspi.pinMiso
		, DmaChannel::Dma2
		};

	adcs =
		{ hspi.AddDevice("adc0", Config::hspi.pinCs[0], Config::SpiFrequency)
		, hspi.AddDevice("adc1", Config::hspi.pinCs[1], Config::SpiFrequency)
		, hspi.AddDevice("adc2", Config::hspi.pinCs[2], Config::SpiFrequency)
		, vspi.AddDevice("adc3", Config::vspi.pinCs[0], Config::SpiFrequency)
		, vspi.AddDevice("adc4", Config::vspi.pinCs[1], Config::SpiFrequency)
		, vspi.AddDevice("adc5", Config::vspi.pinCs[2], Config::SpiFrequency)
		};
}

void AdcController::InitAdcs() {
	PROFILE_FUNCTION();
	esp::logi("Initializing SPI ADCs");

	// Set mode to Auto1 with full input range
	auto setModeAuto1 = Ads7953::SetModeAuto1{};
	setModeAuto1.programSettings = true;
	setModeAuto1.inputRange = Ads7953::InputRange::Full;

	// Disable reading CH15
	auto programModeAuto1 = Ads7953::ProgramModeAuto1{};
	programModeAuto1.channelMask = 0x7fff;

	auto tx = make_unique_dma<Ads7953::Command>();
	auto rx = make_unique_dma<Ads7953::Result>();
	for (auto& adc : adcs) {
		fmt::print("Initializing '{}'\n", adc.GetName());
		Ads7953::Transfer(adc, *rx, *tx, setModeAuto1);
		fmt::print("{:08b} {:08b}\n", rx->data[0], rx->data[1]);
		Ads7953::Transfer(adc, *rx, *tx, programModeAuto1);
		fmt::print("{:08b} {:08b}\n", rx->data[0], rx->data[1]);
		// TODO show error when module is not responding!!!!!!!!!!!!
		// (make a reliable alive check e.g. polling 20 times or so and checking for reasonable result)
	}

	// Continue operation message
	auto continueOperation = Ads7953::ContinueOperation{};

	// Check that every adc is online and correctly
	// programmed by verifying a two full cycles
	for (auto& adc : adcs) {
		Ads7953::Transfer(adc, *rx, *tx, continueOperation);
		int channel = rx->GetChannel();
		for (int i = 0; i < 2 * 15; ++i) {
			int expectedChannel = (channel + 1) % 15;
			Ads7953::Transfer(adc, *rx, *tx, continueOperation);
			if (rx->GetChannel() != expectedChannel) {
				throw OpKeyException("Initialization error: '{}' returned invalid data"_format(adc.GetName()));
			}
			channel = expectedChannel;
		}
	}

	// TODO prepare command DMA buffers
}


#undef CONCAT_IMPL
#undef MACRO_CONCAT
#undef PROFILE_SCOPE
#undef PROFILE_FUNCTION


} // namespace OpKey
