#pragma once

#include "ble_meta.h"
#include "ble_uuid.h"
#include "ble_server.h"


namespace opkey::ble {


static_assert(ESP_OK == 0, "This module relies on the value of ESP_OK to be 0");


static void Init(const char* name);


} // namespace opkey::ble
