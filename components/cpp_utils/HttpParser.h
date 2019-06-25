/*
 * HttpParser.h
 *
 *  Created on: Aug 28, 2017
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


#ifndef CPP_UTILS_HTTPPARSER_H_
#define CPP_UTILS_HTTPPARSER_H_
#include <string>
#include <map>
#include "Socket.h"

class HttpParser {
public:
	HttpParser();
	virtual ~HttpParser();
	std::string getBody();
	std::string getHeader(const std::string& name);
	std::map<std::string, std::string> getHeaders();
	std::string getMethod();
	std::string getURL();
	std::string getVersion();
	std::string getStatus();
	std::string getReason();
	bool hasHeader(const std::string& name);
	void parse(std::string message);
	void parse(Socket s);
	void parseResponse(std::string message);

private:
	std::string m_method;
	std::string m_url;
	std::string m_version;
	std::string m_body;
	std::string m_status;
	std::string m_reason;
	std::map<std::string, std::string> m_headers;
	void dump();
	void parseRequestLine(std::string& line);
	void parseStatusLine(std::string& line);

};

#endif /* CPP_UTILS_HTTPPARSER_H_ */
