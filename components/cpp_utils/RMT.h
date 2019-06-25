/*
 * RMT.h
 *
 *  Created on: Mar 1, 2017
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


#ifndef COMPONENTS_CPP_UTILS_RMT_H_
#define COMPONENTS_CPP_UTILS_RMT_H_
#include <driver/rmt.h>
#include <vector>

/**
 * @brief Drive the %RMT peripheral.
 */
class RMT {
public:
	RMT(gpio_num_t pin, rmt_channel_t channel = RMT_CHANNEL_0);
	virtual ~RMT();
	void add(bool level, uint32_t duration);
	void clear();
	void rxStart();
	void rxStop();
	void txStart();
	void txStop();
	void write();

private:
	rmt_channel_t channel;
	std::vector<rmt_item32_t> items;
	int bitCount = 0;

};

#endif /* COMPONENTS_CPP_UTILS_RMT_H_ */
