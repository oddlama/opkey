#pragma once

#include "entt.h"
#include "exception.h"
#include "rmt_led_strip.h"
#include "spinlock.h"
#include "sensor.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <mutex>


namespace OpKey {


class Application;
class SensorManager;

class Visualizer {
public:
	Visualizer(Application& application);
	~Visualizer() noexcept;

	Visualizer(const Visualizer&) = default;
	Visualizer(Visualizer&&) = default;
	Visualizer& operator=(const Visualizer&) = delete;
	Visualizer& operator=(Visualizer&&) = delete;

	[[noreturn]] void TaskMain();

	void OnTick();
	void OnSensorStateChange(const SensorManager& sensorManager, Sensor sensor);

private:
	xTaskHandle taskHandle = nullptr;
	Spinlock spinlock{};
	bool needsUpdate = false;

#ifndef NDEBUG
	int64_t debugLedFpsTime = 0;
	int64_t debugLedFpsCount = 0;
#endif

	RmtLedStrip<PixelRgbw, RmtTimingsSk6812> ledStrip{GPIO_NUM_32, 288};
	entt::scoped_connection onTickConnection;
	entt::scoped_connection onSensorStateChangeConnection;
};


} // namespace OpKey
