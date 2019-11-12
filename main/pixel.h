#pragma once

#include "color.h"


namespace opkey {


class PixelRgbw {
public:
	inline static uint8_t Convert(double f) noexcept {
		if (f < 0.0) {
			return 0;
		} else if (f >= 1.0) {
			return 0xff;
		}
		return static_cast<uint8_t>(f * 256.0);
	}

public:
	void Clear() {
		g = 0;
		r = 0;
		b = 0;
		w = 0;
	}

	void SetRgb(uint8_t r, uint8_t g, uint8_t b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	void SetRgbw(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->w = w;
	}

	void SetRgb(double r, double g, double b) {
		this->r = Convert(r);
		this->g = Convert(g);
		this->b = Convert(b);
	}

	void SetRgbw(double r, double g, double b, double w) {
		this->r = Convert(r);
		this->g = Convert(g);
		this->b = Convert(b);
		this->w = Convert(w);
	}

	void SetHsv(double hue, double saturation, double value) {
		color::HsvToRgb(*this, hue, saturation, value);
	}

	void SetHsvw(double hue, double saturation, double value, double white) {
		color::HsvToRgb(*this, hue, saturation, value);
		this->w = Convert(w);
	}

	void SetLerp(const PixelRgbw& other, double alpha) {
		double beta = 1.0 - alpha;
		this->r = static_cast<uint8_t>(this->r * beta + other.r * alpha);
		this->g = static_cast<uint8_t>(this->g * beta + other.g * alpha);
		this->b = static_cast<uint8_t>(this->b * beta + other.b * alpha);
		this->w = static_cast<uint8_t>(this->w * beta + other.w * alpha);
	}

	bool operator==(const PixelRgbw& other) const noexcept {
		return
			r == other.r &&
			g == other.g &&
			b == other.b &&
			w == other.w;
	}

	bool operator!=(const PixelRgbw& other) const noexcept {
		 return !(*this == other);
	}

public:
	uint8_t g = 0;
	uint8_t r = 0;
	uint8_t b = 0;
	uint8_t w = 0;
};


} // namespace opkey
