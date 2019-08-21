#pragma once

#include "exception.h"
#include "fmt.h"
#include "config.h"
#include "profiler.h"
#include "sensor_manager.h"
#include "ble_interface.h"
#include "visualizer.h"
#include "statistics.h"

#include "entt/entt.hpp"

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

	const auto& GetSensorManager() const noexcept { return sensorManager; }
	auto& GetOnTickSink() noexcept { return onTickSink; }
	auto& GetOnSensorStateChangeSink() noexcept { return sensorManager.GetOnSensorStateChangeSink(); }

private:
	// Signals
	entt::sigh<void()> onTickSignal{};
	entt::sink<void()> onTickSink{onTickSignal};

	// Different components
	SensorManager sensorManager{*this};
	BleInterface bleInterface{*this};
	Visualizer visualizer{*this};
	Statistics statistics{*this};
};


} // namespace OpKey
