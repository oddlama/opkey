#include "application.h"
#include "dma.h"
#include "error_visualizer.h"
#include "nvs.h"

#include <esp_timer.h>


namespace opkey {


uint8_t midiPacket[] = {
	0x80,  // header
	0x80,  // timestamp, not implemented
	0x00,  // status
	0x3c,  // 0x3c == 60 == middle c
	0x00   // velocity
};

[[noreturn]] void Application::TaskMain(void*) {
	try {
		static Application application{};
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
	xTaskCreatePinnedToCore(&TaskMain, "OpKey", 0x10000, nullptr, tskIDLE_PRIORITY + 1, &taskHandle, opkey::config::MainCore);
}


void Application::operator()() {
	auto& profiler = Profiler::GetInstance();

	profiler.PrintSummary();
	profiler.Reset();

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
	}
}


} // namespace opkey
