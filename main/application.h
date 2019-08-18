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
	[[noreturn]] static void TaskMain(void*);

	/**
	 * Starts a new task for the application
	 */
	static void StartTask();

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
