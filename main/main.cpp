#include <cstdint>
#include <FreeRTOS.h>
#include <freertos/task.h>

#include "sdkconfig.h"
#include "application.h"

extern "C" {
	void app_main();
}

Application application{};

void app_main() {
	application.setCore(CONFIG_PCT_PINNED_TO_CORE);
	application.start();

	// Delete this task
	FreeRTOS::deleteTask();
}
