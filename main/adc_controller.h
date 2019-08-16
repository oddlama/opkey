#pragma once

#include "spi_host.h"
#include "spi_device.h"


namespace OpKey {


class Application;

class AdcController {
public:
	explicit AdcController(Application& application);

	AdcController(const AdcController&) = delete;
	AdcController(AdcController&&) = delete;
	AdcController& operator=(const AdcController&) = delete;
	AdcController& operator=(AdcController&&) = delete;

	//void OnKeyPressed(Key key, double velocity, ) {
	//	invalid = true;
	//}
	//void OnKeyReleased(Key key, ) {
	//	invalid = true;
	//}
	//void Tick() {
	//	key
	//	if (invalid || lastUpdate - now > updateDelayOrFrequencyOrSo) {
	//		invalid = false;

	//		show();
	//	}
	//}

private:
	void InitSpi();
	void InitAdcs();

private:
	Application& application;

	SpiHost hspi{};
	SpiHost vspi{};
	std::array<SpiDevice, Config::NumAdcs> adcs{};
};


} // namespace OpKey
