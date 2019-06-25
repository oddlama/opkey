/*
 * BLExceptions.h
 *
 *  Created on: Nov 27, 2017
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


#ifndef COMPONENTS_CPP_UTILS_BLEEXCEPTIONS_H_
#define COMPONENTS_CPP_UTILS_BLEEXCEPTIONS_H_
#include "sdkconfig.h"

#if CONFIG_CXX_EXCEPTIONS != 1
#error "C++ exception handling must be enabled within make menuconfig. See Compiler Options > Enable C++ Exceptions."
#endif

#include <exception>


class BLEDisconnectedException : public std::exception {
	const char* what() const throw () {
		return "BLE Disconnected";
	}
};

class BLEUuidNotFoundException : public std::exception {
	const char* what() const throw () {
		return "No such UUID";
	}
};

#endif /* COMPONENTS_CPP_UTILS_BLEEXCEPTIONS_H_ */
