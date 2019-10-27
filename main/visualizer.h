#pragma once

#include "entt.h"
#include "exception.h"
#include "rmt_led_strip.h"
#include "spinlock.h"
#include "sensor.h"
#include "sensor_manager.h"
#include "ble_array.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


namespace opkey {


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
	void OnModeChange(Mode oldMode, Mode newMode);
	void OnSensorStateChange(const SensorManager& sensorManager, Sensor sensor);
	void OnMidiRecv(const ble::Array<64>& midiPacket);

private:
	// Task related stuff
	xTaskHandle taskHandle = nullptr;
	//TODO Spinlock spinlock{};
	//TODO bool needsUpdate = false;
	SensorLogicStateData logicStates{};
	// TODO yolo make nice pls
	SensorTensor<double> receivedPresses{};

#ifndef NDEBUG
	int64_t debugLedFpsTime = 0;
	int64_t debugLedFpsCount = 0;
#endif

	// Signals
	entt::scoped_connection onTickConnection;
	entt::scoped_connection onModeChangeConnection;
	entt::scoped_connection onSensorStateChangeConnection;
	entt::scoped_connection onMidiRecvConnection;

	// Led strip and sensor manager ref
	RmtLedStrip<PixelRgbw, RmtTimingsSk6812, 88 * 2 - 1> ledStrip{GPIO_NUM_32};
	const SensorManager& sensorManager;
};


} // namespace opkey
