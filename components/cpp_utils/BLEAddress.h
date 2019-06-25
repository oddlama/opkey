/*
 * BLEAddress.h
 *
 *  Created on: Jul 2, 2017
 *      Author: kolban
 */
/**
 * Original code from nkolban, licensed under Apache-2.0.
 * (See https://github.com/nkolban/esp32-snippets)
 *
 * Modified by oddlama (oddlama@oddlama.org).
 * All modifications are licensed under The MIT License,
 * a copy of which can be found in the 'LICENSE' file at
 * the project's root directory.
 */


#ifndef COMPONENTS_CPP_UTILS_BLEADDRESS_H_
#define COMPONENTS_CPP_UTILS_BLEADDRESS_H_
#include "sdkconfig.h"
#if defined(CONFIG_BT_ENABLED)
#include <esp_gap_ble_api.h> // ESP32 BLE
#include <string>


/**
 * @brief A %BLE device address.
 *
 * Every %BLE device has a unique address which can be used to identify it and form connections.
 */
class BLEAddress {
public:
	BLEAddress(esp_bd_addr_t address);
	BLEAddress(std::string stringAddress);
	bool           equals(BLEAddress otherAddress);
	esp_bd_addr_t* getNative();
	std::string    toString();

private:
	esp_bd_addr_t m_address;
};

#endif /* CONFIG_BT_ENABLED */
#endif /* COMPONENTS_CPP_UTILS_BLEADDRESS_H_ */
