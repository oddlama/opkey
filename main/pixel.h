#pragma once

#include "color.h"


namespace OpKey {


class PixelRgbw {
public:
	void Clear() {
		r = 0;
		g = 0;
		b = 0;
		w = 0;
	}

public:
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t w = 0;
};


} // namespace OpKey
