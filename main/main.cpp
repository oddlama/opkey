#include <cstdint>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "application.h"

extern "C" {
	void app_main();
}

void app_main() {
	OpKey::Application::StartTask();

	// Delete this initial task
	vTaskDelete(nullptr);
}
