#pragma once

#include "mode.h"
#include "exception.h"
#include "fmt.h"
#include "config.h"
#include "profiler.h"
#include "sensor_manager.h"
#include "ble_interface.h"
#include "visualizer.h"
#include "statistics.h"
#include "entt.h"
#include "packet.h"

#include <memory>


namespace opkey {


class Application {
public:
	inline static Application* instance = nullptr;

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

	void SetNextMode(Mode newMode) { nextMode = newMode; }
	auto& GetMode() const noexcept { return mode; }
	auto& GetNextMode() const noexcept { return nextMode; }

	const auto& GetSensorManager() const noexcept { return sensorManager; }
	auto& GetOnTickSink() noexcept { return onTickSink; }
	auto& GetOnModeChangeSink() noexcept { return onModeChangeSink; }

	auto& GetOnSensorStateChangeSignal() noexcept { return onSensorStateChangeSignal; }
	auto& GetOnSensorStateChangeSink() noexcept { return onSensorStateChangeSink; }

	auto& GetOnMidiRecvSignal() noexcept { return onMidiRecvSignal; }
	auto& GetOnMidiRecvSink() noexcept { return onMidiRecvSink; }

private:
	void ApplyNextMode() {
		onModeChangeSignal.publish(mode, nextMode);
		mode = nextMode;
	}

private:
	Mode mode = Mode::Idle;
	Mode nextMode = mode;

	// Signals
	entt::sigh<void()> onTickSignal{};
	entt::sink<void()> onTickSink{onTickSignal};
	entt::sigh<void(Mode, Mode)> onModeChangeSignal{};
	entt::sink<void(Mode, Mode)> onModeChangeSink{onModeChangeSignal};
	entt::sigh<void(const SensorManager&, Sensor sensor)> onSensorStateChangeSignal{};
	entt::sink<void(const SensorManager&, Sensor sensor)> onSensorStateChangeSink{onSensorStateChangeSignal};
	entt::sigh<void(const ble::Array<64>&)> onMidiRecvSignal{};
	entt::sink<void(const ble::Array<64>&)> onMidiRecvSink{onMidiRecvSignal};

	// Different components
	SensorManager sensorManager{*this};
	BleInterface bleInterface{*this};
	Visualizer visualizer{*this};
	Statistics statistics{*this};
};


} // namespace opkey
