#include "application.h"
#include "dma.h"
#include "error_visualizer.h"

#include <esp_timer.h>


namespace OpKey {


uint8_t midiPacket[] = {
	0x80,  // header
	0x80,  // timestamp, not implemented
	0x00,  // status
	0x3c,  // 0x3c == 60 == middle c
	0x00   // velocity
};


[[noreturn]] void Application::TaskMain(void*) {
	try {
		Application{}();
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

static int64_t t = 0;
static int64_t c = 0;

static void VTaskMain(void*) {
	RmtLedStrip<PixelRgbw, RmtTimingsSk6812> ledStrip{GPIO_NUM_32, 2*144};
	while (true) {
		static uint32_t i = 0;
		auto k = i % ledStrip.Size();
		uint8_t r = (i % (ledStrip.Size() *  2)) >= ledStrip.Size()     ? 20 : 0;
		uint8_t g = (i % (ledStrip.Size() *  4)) >= ledStrip.Size() * 2 ? 20 : 0;
		uint8_t b = (i % (ledStrip.Size() *  8)) >= ledStrip.Size() * 4 ? 20 : 0;
		uint8_t w = (i % (ledStrip.Size() * 16)) >= ledStrip.Size() * 8 ? 20 : 0;
		ledStrip[k] = { r, g, b, w };
		++i;
		ledStrip.Update();
		//visualizer.Test();
		++c;
		taskYIELD();
	}
}
void Application::StartTask() {
	xTaskHandle taskHandle = nullptr;
	xTaskCreatePinnedToCore(&TaskMain, "OpKey", 0x10000, nullptr, tskIDLE_PRIORITY + 1, &taskHandle, OpKey::Config::MainCore);
	xTaskCreatePinnedToCore(&VTaskMain, "OpKeyVisualizer", 8192, nullptr, tskIDLE_PRIORITY + 1, &taskHandle, OpKey::Config::VisualizerCore);
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
		auto diff = now - t;
		if (diff > 1000000) {
			fmt::print("Led fps: {}\n", c * 1000000.0 / diff);
			t = now;
			c = 0;
		}
	}
}


} // namespace OpKey
