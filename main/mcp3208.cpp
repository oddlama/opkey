#include "mcp3208.h"


Mcp3208::Mcp3208() {
	spi.init(SPI_MASTER_FREQ_8M / 4, SPI::DEFAULT_CS_PIN);
}

uint16_t Mcp3208::Read(uint8_t channel, bool differential) {
	Command command{channel, differential};
	command.Execute(*this);
	return command.GetValue();
}
