#include <FreeRTOS.h>
#include <freertos/task.h>
#include <cmath>

#include "ads7953.h"


void Ads7953::Init(const SPI::Config& config) noexcept {
	spi.init(config);
}

void Ads7953::Transfer(Result& result, const Command& command) noexcept {
	spi.transfer(result.data.data(), const_cast<Command&>(command).data.data(), command.data.size());
}

void Ads7953::Transfer(Result& result, const ProgramModeAuto1& pma1) noexcept {
	Transfer(result, pma1.ToCommand());
	Transfer(result, pma1.AuxCommand());
}
