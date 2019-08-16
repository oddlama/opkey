#pragma once

#include <WS2812.h>

#include "spi_host.h"
#include "spi_device.h"
#include "ads7953.h"



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
	void InitSpi();
	void InitAdcs();

	void Run();
	void RunStatistics();
	void Calibrate();

private:
#ifdef ENABLE_PROFILING
	DummyProfiler profiler{};
#else
	Profiler profiler{};
#endif

	Config config{};

	// Statistics
	std::chrono::steady_clock::time_point lastStatisticPrint{};
	uint32_t operationCounter = 0;
	uint32_t bleEventCounter = 0;

	// Settings
	size_t multisamples = Config::DefaultMultisamples;

	// Spi
	SpiHost hspi{};
	SpiHost vspi{};
	std::array<SpiDevice, Config::NumAdcs> adcs{};

	// Leds
	WS2812 ws2812{GPIO_NUM_32, 143};
};


} // namespace OpKey
