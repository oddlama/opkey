#pragma once

#include "config.h"
#include "settings.h"
#include "profiler.h"
#include "statistics.h"
#include "adc_controller.h"
#include "ble_server.h"
#include "visualizer.h"



namespace OpKey {


class Application {
public:
	Application() noexcept = default;

	Application(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;

	/**
	 * The main function for the application task.
	 */
	[[noreturn]] static void TaskMain(void*) {
		try {
			Application{}();
		} catch(std::exception& e) {
			esp::loge(LOG_TAG, "Caught exception: {}\nAborting.", e.what());
			abort();
		} catch(...) {
			esp::loge(LOG_TAG, "Caught unkown exception type\nAborting.");
			abort();
		}
		esp::loge(LOG_TAG, "Fatal: Application thread returned!\nAborting.");
		abort();
	}

	/**
	 * Starts a new task for the application
	 */
	static void StartTask() {
		xTaskHandle taskHandle = nullptr;
		xTaskCreatePinnedToCore(&TaskMain, "OpKey", 8192, nullptr, 0, &taskHandle, OpKey::Config::Core);
	}

private:
	void operator()();
	void InitBle();

	void Run();
	void RunStatistics();
	void Calibrate();

private:
	// Persistent application settings
	Settings settings{};

	// Housekeeping components
#ifdef ENABLE_PROFILING
	DummyProfiler profiler{};
#else
	Profiler profiler{};
#endif
	Statistics statistics{};

	// The sensor data history
	SensorHistory history{};

	// Different components
	AdcController adcController{*this};
	BleServer bleServer{*this};
	Visualizer visualizer{*this};
};


} // namespace OpKey
