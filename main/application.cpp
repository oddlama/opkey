#include "application.h"
#include "dma.h"
#include "error_visualizer.h"
#include "nvs.h"
#include "packet.h"

#include <esp_timer.h>
#include <esp_task_wdt.h>


namespace opkey {


[[noreturn]] void Application::TaskMain(void*) {
	try {
		static Application application{};
		Application::instance = &application;
		application();
	} catch(OpKeyException& e) {
		esp::loge("Caught exception: {}\nDevice will abort() and restart in 60 seconds.", e.what());

		ErrorVisualizer visualizer{e};
		int64_t exceptionTime = esp_timer_get_time();
		while (true) {
			visualizer.Tick();

			int64_t now = esp_timer_get_time();
			if (now - exceptionTime > 60 * 1000 * 1000) {
				// restart
				break;
			}

			vTaskDelay(10 / portTICK_PERIOD_MS);
		}

		esp::loge("Aborting.");
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

void Application::StartTask() {
	xTaskHandle taskHandle = nullptr;
	xTaskCreatePinnedToCore(&TaskMain, "OpKey", 0x10000, nullptr, tskIDLE_PRIORITY + 10, &taskHandle, opkey::config::MainCore);
	esp_task_wdt_delete(taskHandle);
}


void Application::operator()() {
	auto& profiler = Profiler::GetInstance();

	profiler.PrintSummary();
	profiler.Reset();

	// Load config, afterwards continue with nextMode
	nextMode = Mode::NormalOperation;
	onModeChangeSignal.publish(mode, Mode::LoadConfig);
	ApplyNextMode();

	while (true) {
		{
			OPKEY_PROFILE_SCOPE("tick");
			onTickSignal.publish();
		}

		int64_t now = esp_timer_get_time();
		if (now - profiler.GetResetTime() > 10000 * 1000) {
			profiler.PrintSummary();
			profiler.Reset();
		}

		if (mode != nextMode) {
			ApplyNextMode();
		}
	}
}


} // namespace opkey
