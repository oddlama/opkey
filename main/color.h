#pragma once


namespace opkey::color {


/** All input ranges are [0.0, 1.0] */
template<typename Color>
inline void HsvToRgb(Color& color, double hue, double saturation, double value) {
	double chroma = value * saturation;
	double prime = fmod(hue * 6.0, 6.0);
	double x = chroma * (1 - fabs(fmod(prime, 2.0) - 1.0));

	double r, g, b;
	if (0.0 <= prime && prime < 1.0) {
		r = chroma;
		g = x;
		b = 0.0;
	} else if (1.0 <= prime && prime < 2.0) {
		r = x;
		g = chroma;
		b = 0.0;
	} else if (2.0 <= prime && prime < 3.0) {
		r = 0.0;
		g = chroma;
		b = x;
	} else if (3.0 <= prime && prime < 4.0) {
		r = 0.0;
		g = x;
		b = chroma;
	} else if (4.0 <= prime && prime < 5.0) {
		r = x;
		g = 0.0;
		b = chroma;
	} else if (5.0 <= prime && prime < 6.0) {
		r = chroma;
		g = 0.0;
		b = x;
	} else {
		r = 0.0;
		g = 0.0;
		b = 0.0;
	}

	double m = value - chroma;
	r += m;
	g += m;
	b += m;

	color.Set(r, g, b);
}


} // namespace opkey::color
