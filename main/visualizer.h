#pragma once

#include "entt.h"
#include "exception.h"
#include "profiler.h"
#include "rmt_led_strip.h"


namespace OpKey {


class Application;

class Visualizer {
public:
	Visualizer(Application& application);

	Visualizer(const Visualizer&) = default;
	Visualizer(Visualizer&&) = default;
	Visualizer& operator=(const Visualizer&) = delete;
	Visualizer& operator=(Visualizer&&) = delete;

	void Test() {
		OPKEY_PROFILE_FUNCTION();
		static uint32_t i = 0;
		auto k = i % ledStrip.Size();
		uint8_t r = (i % (ledStrip.Size() *  2)) >= ledStrip.Size()     ? 20 : 0;
		uint8_t g = (i % (ledStrip.Size() *  4)) >= ledStrip.Size() * 2 ? 20 : 0;
		uint8_t b = (i % (ledStrip.Size() *  8)) >= ledStrip.Size() * 4 ? 20 : 0;
		uint8_t w = (i % (ledStrip.Size() * 16)) >= ledStrip.Size() * 8 ? 20 : 0;
		ledStrip[k] = { r, g, b, w };
		++i;
		ledStrip.Update();
	}

	//void OnKeyPressed(Key key, double velocity, ) {
	//	invalid = true;
	//}
	//void OnKeyReleased(Key key, ) {
	//	invalid = true;
	//}
	//void Tick() {
	//	if (invalid || lastUpdate - now > updateDelayOrFrequencyOrSo) {
	//		invalid = false;

	//		show();
	//	}
	//}

	void OnTick();

private:
	RmtLedStrip<PixelRgbw, RmtTimingsSk6812> ledStrip{GPIO_NUM_32, 144};
	entt::scoped_connection onTickConnection;
};


} // namespace OpKey
