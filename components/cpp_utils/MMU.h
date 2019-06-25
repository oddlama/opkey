/*
 * MMU.h
 *
 *  Created on: Jun 30, 2018
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


#ifndef COMPONENTS_CPP_UTILS_MMU_H_
#define COMPONENTS_CPP_UTILS_MMU_H_
#include <esp_attr.h>
#include <stdint.h>
#include <unistd.h>

class MMU {
public:
	MMU();
	virtual ~MMU();
	static void dump();
	static void mapFlashToVMA(uint32_t flashOffset, void* vma, size_t size);
};

#endif /* COMPONENTS_CPP_UTILS_MMU_H_ */
