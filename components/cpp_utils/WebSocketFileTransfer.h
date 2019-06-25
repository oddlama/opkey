/*
 * WebSocketFileTransfer.h
 *
 *  Created on: Sep 9, 2017
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


#ifndef COMPONENTS_CPP_UTILS_WEBSOCKETFILETRANSFER_H_
#define COMPONENTS_CPP_UTILS_WEBSOCKETFILETRANSFER_H_
#include <string>
#include "WebSocket.h"

class WebSocketFileTransfer {
private:
	WebSocket*    m_pWebSocket;   // The WebSocket over which the file data will arrive.
	std::string   m_rootPath;

public:
	WebSocketFileTransfer(std::string rootPath);
	void start(WebSocket* pWebSocket);
};

#endif /* COMPONENTS_CPP_UTILS_WEBSOCKETFILETRANSFER_H_ */
