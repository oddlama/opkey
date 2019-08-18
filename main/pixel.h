#pragma once

namespace OpKey {


template<size_t Components>
class Pixel {
public:
	std::array<uint8_t, Components> components;
};

class PixelRGBW : public Pixel<4> {
//	ComponentAccessor<0> r;
//	ComponentAccessor<1> g;
//	ComponentAccessor<2> b;
//	ComponentAccessor<3> w;
};


} // namespace OpKey
