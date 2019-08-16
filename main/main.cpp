#include <cstdint>
#include <FreeRTOS.h>
#include <freertos/task.h>

#include "common.h"
#include "application.h"

extern "C" {
	void app_main();
}

void app_main() {
	OpKey::Application::StartTask();

	// Delete this initial task
	FreeRTOS::deleteTask();
}
