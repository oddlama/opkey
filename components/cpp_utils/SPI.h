/*
 * SPI.h
 *
 *  Created on: Mar 3, 2017
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


#ifndef COMPONENTS_CPP_UTILS_SPI_H_
#define COMPONENTS_CPP_UTILS_SPI_H_
#include <driver/spi_master.h>
#include <driver/gpio.h>
/**
 * @brief Handle %SPI protocol.
 */
class SPI {
public:
	struct Config {
		int clockSpeedHz;
		gpio_num_t csPin;
		gpio_num_t mosiPin;
		gpio_num_t misoPin;
		gpio_num_t clkPin;
	};
	SPI();
	virtual ~SPI();
	void    init(
		int clockSpeedHz,
		int csPin,
		int mosiPin = DEFAULT_MOSI_PIN,
		int misoPin = DEFAULT_MISO_PIN,
		int clkPin  = DEFAULT_CLK_PIN
		);
	void    init(const Config& c) {
		init(c.clockSpeedHz, c.csPin, c.mosiPin, c.misoPin, c.clkPin);
	}
	void    setHost(spi_host_device_t host);
	void    transfer(uint8_t* data, size_t dataLen);
	void    transfer(uint8_t* rxData, uint8_t* txData, size_t dataLen);
	uint8_t transferByte(uint8_t value);

	/**
	 * @brief The default MOSI pin.
	 */
	static const int DEFAULT_MOSI_PIN = GPIO_NUM_13;

	/**
	 * @brief The default MISO pin.
	 */
	static const int DEFAULT_MISO_PIN = GPIO_NUM_12;

	/**
	 * @brief The default CLK pin.
	 */
	static const int DEFAULT_CLK_PIN  = GPIO_NUM_14;

	/**
	 * @brief The default CS pin.
	 */
	static const int DEFAULT_CS_PIN   = GPIO_NUM_15;

	/**
	 * @brief Value of unset pin.
	 */
	static const int PIN_NOT_SET	  = -1;

private:
  spi_device_handle_t m_handle;
  spi_host_device_t   m_host;

};

#endif /* COMPONENTS_CPP_UTILS_SPI_H_ */
