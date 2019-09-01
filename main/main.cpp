#include <cstdint>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "application.h"
#include "nvs.h"

extern "C" {
	void app_main();
}

void app_main() {
	opkey::nvs::Init();
	opkey::Application::StartTask();

	// Delete this initial task
	vTaskDelete(nullptr);
}
