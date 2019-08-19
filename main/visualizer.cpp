#include "config.h"
#include "visualizer.h"
#include "application.h"
#include "sensor_manager.h"


namespace OpKey {


Visualizer::Visualizer(Application& application)
	: onTickConnection(application.GetOnTickSink().connect<&Visualizer::OnTick>(*this))
	, onSensorStateChangeConnection(application.GetOnSensorStateChangeSink().connect<&Visualizer::OnSensorStateChange>(*this))
{
	static auto DispatchMain = [](void* param) [[noreturn]] {
		try {
			static_cast<Visualizer*>(param)->TaskMain();
		} catch(std::exception& e) {
			esp::loge("Caught exception: {}\nAborting.", e.what());
			abort();
		} catch(...) {
			esp::loge("Caught unkown exception type\nAborting.");
			abort();
		}
	};

	xTaskCreatePinnedToCore(DispatchMain, "OpKeyVisualizer", 8192, this, tskIDLE_PRIORITY + 1, &taskHandle, OpKey::Config::VisualizerCore);
}

Visualizer::~Visualizer() noexcept {
	vTaskDelete(taskHandle);
}


void Visualizer::TaskMain() {
	static int r = 0;
	while (true) {
		if (++r % 2 == 0) {
			// Decay
			for (size_t i = 0; i < ledStrip.Size(); ++i) {
				if (ledStrip[i].r > 0) { ledStrip[i].r -= 1; needsUpdate = true; }
				if (ledStrip[i].g > 0) { ledStrip[i].g -= 1; needsUpdate = true; }
				if (ledStrip[i].b > 0) { ledStrip[i].b -= 1; needsUpdate = true; }
				if (ledStrip[i].w > 0) { ledStrip[i].w -= 1; needsUpdate = true; }
			}
		}
		do {
			//std::scoped_lock lock{spinlock};

			if (not needsUpdate) {
				break;
			}
			needsUpdate = false;

			//static uint32_t i = 0;
			//auto k = i % ledStrip.Size();
			//uint8_t r = (i % (ledStrip.Size() *  2)) >= ledStrip.Size()     ? 20 : 0;
			//uint8_t g = (i % (ledStrip.Size() *  4)) >= ledStrip.Size() * 2 ? 20 : 0;
			//uint8_t b = (i % (ledStrip.Size() *  8)) >= ledStrip.Size() * 4 ? 20 : 0;
			//uint8_t w = (i % (ledStrip.Size() * 16)) >= ledStrip.Size() * 8 ? 20 : 0;
			//ledStrip[k] = { r, g, b, w };
			//++i;
			ledStrip.Update();

			++debugLedFpsCount;
		} while (false);

		// yeet!
		vTaskDelay(10 / portTICK_PERIOD_MS);
		taskYIELD();
	}
}


void Visualizer::OnTick() {
	OPKEY_PROFILE_FUNCTION();

#ifndef NDEBUG
	int64_t now = esp_timer_get_time();
	auto diff = now - debugLedFpsTime;
	if (diff > 1000000) {
		fmt::print("Visualizer fps: {}\n", debugLedFpsCount * 1000000.0 / diff);
		debugLedFpsTime = now;
		debugLedFpsCount = 0;
	}
#endif
}

void Visualizer::OnSensorStateChange(const SensorManager& sensorManager, Sensor sensor) {
	if (sensor.IsPedal()) {
		return;
	}

	auto& h0 = sensorManager.GetHistory()[0];
	auto& keyState = h0.keyState[sensor];

	//std::scoped_lock lock{spinlock};

	size_t ledIndex = (Sensor::KeyCount - 1) - sensor.GetKeyIndex();
	if (keyState.pressed) {
		ledStrip[ledIndex] = { 0, 20, 30, 10 };
	} else {
		// TODO ledStrip[ledIndex] = { };
	}

	needsUpdate = true;
}


} // namespace OpKey
