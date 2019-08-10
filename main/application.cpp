#include <driver/adc.h>

#include "common.h"
#include "application.h"


namespace OpKey {


static const char* LOG_TAG = "OpKey";

#define SERVICE_UUID        "03b80e5a-ede8-4b33-a751-6ce34ec4c700"
#define CHARACTERISTIC_UUID "7772e5db-3868-4112-a1a9-f2669d106bf3"

template<typename T>
T* DmaMalloc(size_t size) {
	return static_cast<T*>(heap_caps_malloc(size, MALLOC_CAP_DMA));
}

template<typename T, typename... Args>
T* DmaNew(Args&&... args) {
	T* t = DmaMalloc<T>(sizeof(T));
	new(t) T(std::forward<Args>(args)...);
	return t;
}

struct DmaDelete {
	void operator()(void* ptr) {
		heap_caps_free(ptr);
	}
};

template<typename T>
using unique_ptr_dma = std::unique_ptr<T, DmaDelete>;

template<typename T, typename... Args>
unique_ptr_dma<T> make_unique_dma(Args&&... args) {
	return unique_ptr_dma<T>(DmaNew<T>(std::forward<Args>(args)...));
}



uint8_t midiPacket[] = {
	0x80,  // header
	0x80,  // timestamp, not implemented
	0x00,  // status
	0x3c,  // 0x3c == 60 == middle c
	0x00   // velocity
};

void Application::onConnect(BLEServer* server) {
	esp::logi(LOG_TAG, "BLE connected");
	deviceConnected = true;
	resume();
}

void Application::onDisconnect(BLEServer* server) {
	esp::logi(LOG_TAG, "BLE disconnected");
	deviceConnected = false;
}

void Application::InitBle() {
	esp::logi(LOG_TAG, "Initializing BLE");
	BLEDevice::init("OpKey");

	// Create the BLE Server
	BLEServer* server = BLEDevice::createServer();
	server->setCallbacks(this);

	// Create the BLE Service
	BLEService* service = server->createService(BLEUUID(SERVICE_UUID));

	// Create a BLE Characteristic
	characteristic = service->createCharacteristic
		( BLEUUID(CHARACTERISTIC_UUID)
		, BLECharacteristic::PROPERTY_READ
			| BLECharacteristic::PROPERTY_WRITE
			| BLECharacteristic::PROPERTY_NOTIFY
			| BLECharacteristic::PROPERTY_WRITE_NR
		);

	// https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
	// Create a BLE Descriptor
	characteristic->addDescriptor(new BLE2902());

	// Start the service
	service->start();

	// Start advertising
	BLEAdvertising* advertising = server->getAdvertising();
	advertising->addServiceUUID(service->getUUID());
	advertising->start();
	esp::logi(LOG_TAG, "BLE advertising");
}

void Application::InitSpi() {
	esp::logi(LOG_TAG, "Initializing SPI");
	hspi = SpiHost
		{ "hspi"
		, SpiHost::HostDevice::Hspi
		, Config::hspi.pinSclk
		, Config::hspi.pinMosi
		, Config::hspi.pinMiso
		, SpiHost::DmaChannel::Dma1
		};

	vspi = SpiHost
		{ "vspi"
		, SpiHost::HostDevice::Vspi
		, Config::vspi.pinSclk
		, Config::vspi.pinMosi
		, Config::vspi.pinMiso
		, SpiHost::DmaChannel::Dma2
		};

	adcs =
		{ hspi.AddDevice("adc0", Config::hspi.pinCs[0], Config::SpiFrequency)
		, hspi.AddDevice("adc1", Config::hspi.pinCs[1], Config::SpiFrequency)
		, hspi.AddDevice("adc2", Config::hspi.pinCs[2], Config::SpiFrequency)
		, vspi.AddDevice("adc3", Config::vspi.pinCs[0], Config::SpiFrequency)
		, vspi.AddDevice("adc4", Config::vspi.pinCs[1], Config::SpiFrequency)
		, vspi.AddDevice("adc5", Config::vspi.pinCs[2], Config::SpiFrequency)
		};
}

void Application::InitAdcs() {
	esp::logi(LOG_TAG, "Initializing SPI ADCs");

	// Set mode to Auto1 with full input range
	auto setModeAuto1 = Ads7953::SetModeAuto1{};
	setModeAuto1.programSettings = true;
	setModeAuto1.inputRange = Ads7953::InputRange::Full;

	// Disable reading CH15
	auto programModeAuto1 = Ads7953::ProgramModeAuto1{};
	programModeAuto1.channelMask = 0x7fff;

	auto tx = make_unique_dma<Ads7953::Command>();
	auto rx = make_unique_dma<Ads7953::Result>();
	for (auto& adc : adcs) {
		fmt::print("Initializing '{}'\n", adc.GetName());
		Ads7953::Transfer(adc, *rx, *tx, setModeAuto1);
		fmt::print("{:08b} {:08b}\n", rx->data[0], rx->data[1]);
		Ads7953::Transfer(adc, *rx, *tx, programModeAuto1);
		fmt::print("{:08b} {:08b}\n", rx->data[0], rx->data[1]);
		// TODO show error when module is not responding!!!!!!!!!!!!
		// (make a reliable alive check e.g. polling 20 times or so and checking for reasonable result)
	}

	// TODO prepare command DMA buffers
}

void Application::Run() {
	// TODO BAAAAAAAAAAAH! static
	static auto tx = make_unique_dma<Ads7953::Command>();
	static auto rx = make_unique_dma<Ads7953::Result>();
	*tx = Ads7953::ContinueOperation{}.ToCommand();

	std::array<uint32_t, Config::NumAdcs * Config::NumChannels> channelValues{};

	for (int s = 0; s < multisamples; ++s) {
		for (int a = 0; a < Config::NumAdcs; ++a) {
			if (a == 3) continue;
			for (int c = 0; c < Config::NumChannels; ++c) {
				adcs[a].Transfer(rx->data.data(), rx->data.size(), tx->data.data(), tx->data.size());
				channelValues[a * Config::NumChannels + rx->GetChannel()] += rx->GetValue();
			}
		}
	}

	for (int i = 0; i < Config::NumAdcs * Config::NumChannels; ++i) {
		double val = channelValues[i];
		val /= multisamples;
		val = sqrt(val) / 64 * 255.0;

		int v = val;
		if (v < 10) {
			v = 0;
		} else if (v > 255) {
			v = 255;
		}

		//int valdiff = oldValues[i] - values[i];
		//if (valdiff > 0) {
		//	ws2812.setPixel(i, 0, 0, valdiff);
		//} else {
		//	ws2812.setPixel(i, 0, -valdiff, 0);
		//}
		ws2812.setPixel(i, 0, v / 2, v);
	}
	ws2812.show();

	++operationCounter;
	RunStatistics();
}

void Application::RunStatistics() {
	auto now = std::chrono::steady_clock::now();
	double secondsSinceLastPrint = std::chrono::duration_cast<std::chrono::duration<double>>(now - lastStatisticPrint).count();
	if (secondsSinceLastPrint >= 1.0) {
		constexpr const size_t monitoredChannels = Config::NumChannels * Config::NumAdcs;

		double effectiveSamplingRate = operationCounter / secondsSinceLastPrint;
		double rawSamplingRate = operationCounter * monitoredChannels;
		double totalSamplingRate = rawSamplingRate * multisamples;

		double bleEventRate = bleEventCounter / secondsSinceLastPrint;

		fmt::print("Statistics:\n");
		fmt::print("  monitored channels:          {:6d}\n",   monitoredChannels);
		fmt::print("  multisamples:                {:6d}\n",   multisamples);
		fmt::print("  samples/(ch*s) (effective):  {:9.2f}\n", effectiveSamplingRate);
		fmt::print("  samples/(ch*s) (raw):        {:9.2f}\n", rawSamplingRate);
		fmt::print("  samples/s (total):           {:9.2f}\n", totalSamplingRate);
		fmt::print("  BLE events/s:                {:9.2f}\n", bleEventRate);

		operationCounter = 0;
		bleEventCounter = 0;
		lastStatisticPrint = std::chrono::steady_clock::now();
	}
}

void Application::Calibrate() {
	esp::logi(LOG_TAG, "Entering calibration mode");
}

void Application::operator()() {
	try {
		InitBle();
		// A little time
		vTaskDelay(100 / portTICK_PERIOD_MS);
		InitSpi();
		InitAdcs();

		lastStatisticPrint = std::chrono::steady_clock::now();

		// TODO remove
		esp::loge(LOG_TAG, "REMOVE DEBUG");
		multisamples = 1;

		while (true) {
			switch (mode) {
				case Mode::Run:
					Run();
					break;

				case Mode::Calibrate:
					Calibrate();
					break;
			}
		}

		// start auxiliary thread (visualization, non realtime stuff, other cpu.)

		//init adcs
		//prepare dma command and result queues for both dma channels
		//	//for nsamples:
		//	//	for adc : adcs
		//	//		retrieve Config::NumChannels samples (full readout)
		//	//	average samples

		//while true:
		//	switch mode:
		//		calibrate:
		//			//init all LEDs red
		//			//led[all keys + pedals???] = Color::calibrateMinimum;
		//			for 2 seconds:
		//				record min values,
		//				average normal min values,

		//			//led[all keys + pedals???] = Color::calibratedMaximum;
		//			until all keys ready and (press finish???):
		//				record max values
		//				average normal max value (only register values > threshold?
		//				//led[calibrated key with >1000 good samples] = Color::keyCalibrated;

		//		run:
		//			std::array<Keytable, N> processing buffer
		//			queue = pointer to tables.

		//			send prepared dma buffers
		//			average samples for each key
		//			* apply calibration
		//			busy wait for empty processing queue slot
		//			swap pointer in queue

		//			velocity = calculate difference to last sample
		//			acceleration = calculate difference to last velocity

		//			if acceleration is negative:
		//				if velocity > threshold:
		//					if position > threshold:
		//						send key down:

		//			if position < minthreshold:
		//				send key up.
	} catch(std::exception& e) {
		esp::loge(LOG_TAG, "Caught exception: {}\nAborting.", e.what());
		abort();
	}
}


} // namespace OpKey
