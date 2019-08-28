#include <cstdint>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "application.h"

extern "C" {
	void app_main();
}

void app_main() {
	opkey::Application::StartTask();

	// Delete this initial task
	vTaskDelete(nullptr);
}
