/*
 * SSLUtils.h
 *
 *  Created on: Sep 16, 2017
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


#ifndef COMPONENTS_CPP_UTILS_SSLUTILS_H_
#define COMPONENTS_CPP_UTILS_SSLUTILS_H_
#include <string>
class SSLUtils {
private:
	static char* m_certificate;
	static char* m_key;
public:
	SSLUtils();
	virtual ~SSLUtils();
	static void setCertificate(std::string certificate);
	static char* getCertificate();
	static void setKey(std::string key);
	static char* getKey();
};

#endif /* COMPONENTS_CPP_UTILS_SSLUTILS_H_ */
