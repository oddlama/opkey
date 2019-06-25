/*
 * IFTTT.h
 *
 *  Created on: Mar 14, 2017
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


#ifndef MAIN_IFTTT_H_
#define MAIN_IFTTT_H_

#include <RESTClient.h>
#include <string>
/**
 * @brief Encapsulate %IFTTT calls.
 */
class IFTTT {
public:
	IFTTT(std::string key);
	virtual ~IFTTT();
	void trigger(std::string event, std::string value1 = "", std::string value2 = "", std::string value3 = "");
private:
	RESTClient m_restClient;
	std::string m_key;
};

#endif /* MAIN_IFTTT_H_ */
