/*
 * SOC.h
 *
 *  Created on: May 16, 2017
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


#ifndef COMPONENTS_CPP_UTILS_SOC_H_
#define COMPONENTS_CPP_UTILS_SOC_H_

class SOC {
public:
	SOC();
	virtual ~SOC();
	class I2S {
	public:
		static void dump();
	};
};

#endif /* COMPONENTS_CPP_UTILS_SOC_H_ */
