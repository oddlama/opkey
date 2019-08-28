#pragma once

#include "color.h"


namespace opkey {


class PixelRgbw {
public:
	void Clear() {
		g = 0;
		r = 0;
		b = 0;
		w = 0;
	}

public:
	uint8_t g = 0;
	uint8_t r = 0;
	uint8_t b = 0;
	uint8_t w = 0;
};


} // namespace opkey
