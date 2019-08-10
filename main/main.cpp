#include <cstdint>
#include <FreeRTOS.h>
#include <freertos/task.h>

#include "common.h"
#include "application.h"

extern "C" {
	void app_main();
}

OpKey::Application application{};

void app_main() {
	application.setCore(OpKey::Config::Core);
	application.start();

	// Delete this task
	FreeRTOS::deleteTask();
}
