#pragma once

#include "exception.h"
#include "fmt.h"
#include "config.h"
#include "settings.h"
#include "profiler.h"
#include "sensor_history.h"
#include "adc_controller.h"
#include "ble_server.h"
#include "visualizer.h"
#include "statistics.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <memory>


namespace OpKey {


class Application {
public:
	Application() = default;

	Application(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;

public:
	/**
	 * The main function for the application task.
	 */
	[[noreturn]] static void TaskMain(void*) {
		try {
			Application{}();
		} catch(OpKeyException& e) {
			esp::loge("Caught exception: {}\nDevice will abort() and restart in 60 seconds.", e.what());
			// TODO start visualizer loop to notify user.
			vTaskDelay(60 * 1000 / portTICK_PERIOD_MS);
			abort();
		} catch(std::exception& e) {
			esp::loge("Caught exception: {}\nAborting.", e.what());
			abort();
		} catch(...) {
			esp::loge("Caught unkown exception type\nAborting.");
			abort();
		}
		esp::loge("Fatal: Application thread returned!\nAborting.");
		abort();
	}

	/**
	 * Starts a new task for the application
	 */
	static void StartTask() {
		xTaskHandle taskHandle = nullptr;
		xTaskCreatePinnedToCore(&TaskMain, "OpKey", 8192, nullptr, 0, &taskHandle, OpKey::Config::Core);
	}

public:
	void operator()();

private:
	// Persistent application settings
	Settings settings{};

	// The sensor data history
	SensorHistory<5> history{};

	// Different components
	AdcController adcController{};
	BleServer bleServer{};
	Visualizer visualizer{};
	Statistics statistics{};
};


} // namespace OpKey
