#pragma once

#include "exception.h"
#include "profiler.h"
#include "rmt_led_strip.h"


namespace OpKey {


class ErrorVisualizer {
public:
	ErrorVisualizer(OpKeyException& e) {
		// TODO blink whole strip 3 times, then lock on error code (binary red yellow).
	}

	ErrorVisualizer(const ErrorVisualizer&) = default;
	ErrorVisualizer(ErrorVisualizer&&) = default;
	ErrorVisualizer& operator=(const ErrorVisualizer&) = delete;
	ErrorVisualizer& operator=(ErrorVisualizer&&) = delete;

	void Tick();

private:
	RmtLedStrip<PixelRgbw, RmtTimingsSk6812> ledStrip{GPIO_NUM_32, 144};
};


} // namespace OpKey
