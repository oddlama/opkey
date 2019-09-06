#pragma once

#include "entt.h"


namespace opkey {


enum class Mode : uint8_t {
	Idle,
	LoadConfig,
	NormalOperation,
	Calibrate,
	_EnumMax,
};


} // namespace opkey
