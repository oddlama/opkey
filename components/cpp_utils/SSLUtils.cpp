/*
 * SSLUtils.cpp
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


#include "SSLUtils.h"
#include <stdlib.h>
#include <string.h>

char* SSLUtils::m_certificate = nullptr;
char* SSLUtils::m_key = nullptr;

SSLUtils::SSLUtils() {
}

SSLUtils::~SSLUtils() {
}

void SSLUtils::setCertificate(std::string certificate) {
	size_t len = certificate.length();
	m_certificate = (char*) malloc(len + 1);
	memcpy(m_certificate, certificate.data(), len);
	m_certificate[len] = '\0';
}

char* SSLUtils::getCertificate() {
	return m_certificate;
}

void SSLUtils::setKey(std::string key) {
	size_t len = key.length();
	m_key = (char*) malloc(len + 1);
	memcpy(m_key, key.data(), len);
	m_key[len] = '\0';
}

char* SSLUtils::getKey() {
	return m_key;
}
