/*
 * File.h
 *
 *  Created on: Jun 1, 2017
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


#ifndef COMPONENTS_CPP_UTILS_FILE_H_
#define COMPONENTS_CPP_UTILS_FILE_H_
#include <string>
#include <dirent.h>

/**
 * @brief A logical representation of a file.
 */
class File {
public:
	File(std::string name, uint8_t type = DT_UNKNOWN);

	std::string getContent(bool base64Encode = false);
	std::string getContent(uint32_t offset, uint32_t size);
	std::string getName();
	std::string getPath();
	uint8_t     getType();
	bool        isDirectory();
	uint32_t    length();

private:
	std::string m_path;
	uint8_t     m_type;
};

#endif /* COMPONENTS_CPP_UTILS_FILE_H_ */
