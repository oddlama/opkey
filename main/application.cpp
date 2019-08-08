#include <driver/adc.h>
#include <WS2812.h>

#include "common.h"
#include "application.h"
#include "spi_host.h"

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
	ESP_LOGI(LOG_TAG, "BLE connected");
	deviceConnected = true;
	resume();
}

void Application::onDisconnect(BLEServer* server) {
	ESP_LOGI(LOG_TAG, "BLE disconnected");
	deviceConnected = false;
}

void Application::BLEInit() {
	ESP_LOGI(LOG_TAG, "Init BLE");
	BLEDevice::init("OpKey");

	// Create the BLE Server
	BLEServer* server = BLEDevice::createServer();
	server->setCallbacks(this);

	// Create the BLE Service
	BLEService* service = server->createService(BLEUUID(SERVICE_UUID));

	// Create a BLE Characteristic
	characteristic = service->createCharacteristic(
			BLEUUID(CHARACTERISTIC_UUID),
			BLECharacteristic::PROPERTY_READ   |
			BLECharacteristic::PROPERTY_WRITE  |
			BLECharacteristic::PROPERTY_NOTIFY |
			BLECharacteristic::PROPERTY_WRITE_NR
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
}

void Application::operator()() {
	try {
		//setvbuf(stdout, nullptr, _IONBF, 0);
		BLEInit();

		gpio_num_t hSpiMiso = GPIO_NUM_12;
		gpio_num_t hSpiMosi = GPIO_NUM_13;
		gpio_num_t hSpiSclk = GPIO_NUM_14;
		gpio_num_t hSpiCs0  = GPIO_NUM_15;
		gpio_num_t hSpiCs1  = GPIO_NUM_16;
		gpio_num_t hSpiCs2  = GPIO_NUM_17;
		gpio_num_t vSpiMiso = GPIO_NUM_19;
		gpio_num_t vSpiMosi = GPIO_NUM_23;
		gpio_num_t vSpiSclk = GPIO_NUM_18;
		gpio_num_t vSpiCs0  = GPIO_NUM_5;
		gpio_num_t vSpiCs1  = GPIO_NUM_25;
		gpio_num_t vSpiCs2  = GPIO_NUM_26;

		auto hspi = SpiHost{SpiHost::HostDevice::Hspi, hSpiSclk, hSpiMosi, hSpiMiso, SpiHost::DmaChannel::Dma1};
		auto vspi = SpiHost{SpiHost::HostDevice::Vspi, vSpiSclk, vSpiMosi, vSpiMiso, SpiHost::DmaChannel::Dma1};
		auto adc0 = hspi.AddDevice(hSpiCs0, SPI_MASTER_FREQ_20M);
		auto adc1 = hspi.AddDevice(hSpiCs1, SPI_MASTER_FREQ_20M);
		auto adc2 = hspi.AddDevice(hSpiCs2, SPI_MASTER_FREQ_20M);
		auto adc3 = vspi.AddDevice(vSpiCs0, SPI_MASTER_FREQ_20M);
		auto adc4 = vspi.AddDevice(vSpiCs1, SPI_MASTER_FREQ_20M);
		auto adc5 = vspi.AddDevice(vSpiCs2, SPI_MASTER_FREQ_20M);

		//std::array<Mcp3208::Command, 8> readChannel{};
		//for (int c = 0; c < 8; ++c) {
		//	readChannel[c] = Mcp3208::Command(c, false);
		//}

		//Mcp3208::Command* commandQueue = (Mcp3208::Command*)heap_caps_malloc(sizeof(Mcp3208::Command) * 100, MALLOC_CAP_DMA);
		//auto Sample100 = [&](int c) {
		//	int ival = 0;
		//	for (int i = 0; i < 100; ++i) {
		//		commandQueue[i] = readChannel[c];
		//	}
		//	Mcp3208::Command::Execute(mcp, commandQueue, 100);
		//	for (int i = 0; i < 100; ++i) {
		//		ival += commandQueue[i].GetValue();
		//	}
		//	return ival / 100;
		//};

		//int gi = 0;
		//while (true) {
		//std::array<Ads7953, 6> adcs{};

		//std::array<SPI::Config, 6> spiConfigs =
		//	{{ { SPI_MASTER_FREQ_20M, hSpiCs0, hSpiMosi, hSpiMiso, hSpiSclk }
		//	, { SPI_MASTER_FREQ_20M, hSpiCs1, hSpiMosi, hSpiMiso, hSpiSclk }
		//	, { SPI_MASTER_FREQ_20M, hSpiCs2, hSpiMosi, hSpiMiso, hSpiSclk }
		//	, { SPI_MASTER_FREQ_20M, vSpiCs0, vSpiMosi, vSpiMiso, vSpiSclk }
		//	, { SPI_MASTER_FREQ_20M, vSpiCs1, vSpiMosi, vSpiMiso, vSpiSclk }
		//	, { SPI_MASTER_FREQ_20M, vSpiCs2, vSpiMosi, vSpiMiso, vSpiSclk }
		//	}};

		//for (int i = 0; i < 6; ++i) {
		//	if (gi == i)
		//	adcs[i].Init(spiConfigs[i]);
		//}

		//struct Commands {
		//	Ads7953::Command setModeAuto1{};
		//	Ads7953::Command programModeAuto1{};
		//	Ads7953::Command continueOperation{};
		//};

		//auto result = make_unique_dma<Ads7953::Result>();
		//auto commands = make_unique_dma<Commands>();

		//// Set Auto1 with full input range
		//auto setModeAuto1 = Ads7953::SetModeAuto1{};
		//setModeAuto1.programSettings = true;
		//setModeAuto1.inputRange = Ads7953::InputRange::Full;
		//commands->setModeAuto1 = setModeAuto1;

		//// Disable CH15
		//auto programModeAuto1 = Ads7953::ProgramModeAuto1{};
		//programModeAuto1.channelMask = 0x7fff;
		//commands->programModeAuto1 = programModeAuto1;

		//int i = 0;
		//for (auto& adc : adcs) {
		//	if (gi == i)
		//	{
		//	adc.Transfer(*result, commands->setModeAuto1);
		//	adc.Transfer(*result, commands->programModeAuto1);
		//	}
		//	++i;
		//}

		//// Prepare continue command
		//commands->continueOperation = Ads7953::ContinueOperation{};




		//while (true) {
		//	int i = 0;
		//	for (auto& adc : adcs) {
		//		if (gi == i)
		//		{
		//		for (int i = 0; i < 15; ++i) {
		//			adc.Transfer(*result, commands->continueOperation);
		//			printf("ADC %p CH%02d: %4.1f\n", (void*)&adc, result->GetChannel(), sqrt(0.0 + result->GetValue()));
		//		}
		//		}
		//		++i;
		//		//double chanVal[16];
		//		//for (int i = 0; i < 16; ++i) {
		//		//	adc.spi.transfer(dmaBuf, dataRunAuto1, 2);
		//		//	uint8_t chan = (dmaBuf[0] & 0xf0) >> 4;
		//		//	uint16_t result = dmaBuf[0] & 0x0f;
		//		//	result <<= 8;
		//		//	result |= dmaBuf[1];
		//		//	double d = sqrt(result);
		//		//	chanVal[chan] = d;
		//		//	//printf("%4.1f ", d);
		//		//	//if (chan == 15) {
		//		//	//	printf("\n");
		//		//	//}
		//		//}
		//		//for (int i = 0; i < 143; ++i) {
		//		//	int val = chanVal[i % 13] / 64.0 * 255;
		//		//	ws2812.setPixel(i, val, val, val);
		//		//}
		//		//ws2812.show();
		//		vTaskDelay(1000 / portTICK_PERIOD_MS);
		//	}
		//	break;
		//}
		//}

		WS2812 ws2812{GPIO_NUM_32, 143};
		//static int offset = 0.0;
		static int current = 0;

		//while (true) {
		//	for (int i = 0; i < 143; ++i) {
		//		double distance = abs(i - current);
		//		int val = 255.0 / (1 + distance * distance);
		//		ws2812.setPixel(i, val, val, val);
		//	}
		//	ws2812.show();
		//	++current;
		//	if (current == 143) {
		//		current = 0;
		//	}
		//	vTaskDelay(10 / portTICK_PERIOD_MS);
		//}

		//adc.Read();

		//uint8_t* dataRunAuto1 = (uint8_t*)heap_caps_malloc(2, MALLOC_CAP_DMA);
		//dataRunAuto1[0] = 0b00100000;
		//dataRunAuto1[1] = 0b00000000;
		//uint8_t* dmaBuf = (uint8_t*)heap_caps_malloc(2, MALLOC_CAP_DMA);

		//dmaBuf[0] = 0;
		//dmaBuf[1] = 0;
		//while (true) {
		//	// skip to chan 0
		//	while ((dmaBuf[0] & 0xf0) != 0xf0) {
		//		adc.spi.transfer(dmaBuf, dataRunAuto1, 2);
		//	}
		//	double chanVal[16];
		//	for (int i = 0; i < 16; ++i) {
		//		adc.spi.transfer(dmaBuf, dataRunAuto1, 2);
		//		uint8_t chan = (dmaBuf[0] & 0xf0) >> 4;
		//		uint16_t result = dmaBuf[0] & 0x0f;
		//		result <<= 8;
		//		result |= dmaBuf[1];
		//		double d = sqrt(result);
		//		chanVal[chan] = d;
		//		//printf("%4.1f ", d);
		//		//if (chan == 15) {
		//		//	printf("\n");
		//		//}
		//	}
		//	for (int i = 0; i < 143; ++i) {
		//		int val = chanVal[i % 13] / 64.0 * 255;
		//		ws2812.setPixel(i, val, val, val);
		//	}
		//	ws2812.show();
		//	vTaskDelay(10 / portTICK_PERIOD_MS);
		//}

		//heap_caps_free(dmaBuf);
		//heap_caps_free(dataRunAuto1);

		while (true) {
			static unsigned long last = 0;
			//static uint32_t cycles = 0;
			if (deviceConnected) {
			} else {
				//for (int i = 0; i < 7; ++i) {
				//	ws2812.setHSBPixel(i, (offset + (i * 50)) % 360, (offset / 3) % 256, offset % 256);
				//}
				//ws2812.show();
				//for (int i = 0; i < 7; ++i) {
				//	ws2812.setPixel(i, 0, 0, 0);
				//}
				//ws2812.setPixel(offset % 7, 255, 255, 255);
				//ws2812.show();
				//++offset;
				//float a1 = 4.1234;
				//float a2 = 1.2345;
				//float a3 = 0;
				//float t = 0;
				//int a = -1;
				//for (int i = 0; i < 100000; ++i) {
				//	a3 = a1 - a2;
				//	a1 += a;
				//	t += a3;
				//	a = -a;
				//}
				//auto now = esp_timer_get_time();
				//double frac = 1000000.0 / (now - last);
				//printf("%6.3f flops (100k in %7.3f sec)\n", 100000.0 * frac, 1.0 / frac);
				//last = now;
				//auto ReadCh = [&](int c) {
				//	int multisample = 1000;//00;
				//	int ival = 0;
				//	for (int i = 0; i < multisample; ++i) {
				//		ival += Sample100(c);
				//		//ival += mcp.Read(readChannel[c]);
				//	}
				//	double val = static_cast<double>(ival) / multisample;
				//	return val;
				//};
				//for (int c = 0; c < 8; ++c) {
				//	printf("%6.1f (c%d), ", ReadCh(c), c);
				//}
				//printf("\n");
				//auto now = esp_timer_get_time();
				//double frac = 1000000.0 / (now - last);
				//printf("%6.3f ksps (800k in %7.3f sec) multisample per sensor at 480 Hz: %6.3f sps\n", 800.0 * frac, 1.0 / frac, 8000.0 / 9.0 / 48 * frac);
				//last = now;
				//vTaskDelay(1000 / portTICK_PERIOD_MS);

				//spi.init();
				//auto ReadAdc(int channel) {
				//	// commandByte = start(1), mode(1), channel(3), don't care(3)
				//	uint8_t commandByte = 0b11000000 | (channel << 3);
				//}
				//for (int c = 0; c < 8; ++c) {
				//	spi.transferByte(0x0);
				//	spi.transferByte(0x0);
				//}
				//spi.transferByte(0x0);
				//spi.transferByte(0x0);

				//characteristic->setValue(midiPacket, 5); // packet, length in bytes
				//for (int i = 0; i < 90; ++i) {
				//	// note down
				//	midiPacket[2] = 0x90; // note down, channel 0
				//	midiPacket[4] = 127;  // velocity
				//	characteristic->notify();
				//}

				//for (int i = 0; i < 90; ++i) {
				//	// note up
				//	midiPacket[2] = 0x80; // note up, channel 0
				//	midiPacket[4] = 0;    // velocity
				//	//characteristic->setValue(midiPacket, 5); // packet, length in bytes)
				//	characteristic->notify();
				//}
				//// play note for 500ms
				//vTaskDelay(500 / portTICK_PERIOD_MS);

				//adc1_config_width(ADC_WIDTH_BIT_12);
				//adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
				//adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);
				//adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);

				//const int adcSteps = 4096;

				//auto InternalAdcSample = [&](auto channel) {
				//	const int multisample = 64;
				//	int ival = 0;
				//	for (int i = 0; i < multisample; ++i) {
				//		ival += adc1_get_raw(channel);
				//	}
				//	double val = (double)ival / multisample;
				//	return val;
				//};

				//printf("%7.3f %7.3f %7.3f\n", InternalAdcSample(ADC1_CHANNEL_0), InternalAdcSample(ADC1_CHANNEL_3), InternalAdcSample(ADC1_CHANNEL_6));
				//vTaskDelay(10 / portTICK_PERIOD_MS);


				//static double lastVal = 0.0;
				//// to distance
				//val = sqrt(val);
				//double diff = val - lastVal;
				//lastVal = val;

				//printf("val %7.3f diff %+7.3f\n", val, diff);

				//// Print absolute scale
				//const int termWidth = 200;
				//const double stepsPerChar = sqrt(static_cast<double>(adcSteps)) / termWidth;
				//double chars = val / stepsPerChar;
				//int fullChars = static_cast<int>(chars);
				//int lastCharIndex = static_cast<int>((chars - fullChars) * 8);
				//const char* bar = "████████████████";
				//const char* lastChar= "▏▎▍▌▋▊▉█";
				//int i = 0;

				//dprintf(STDOUT_FILENO, "[2K%6.1f %+6.1f", val, diff);
				//for (i = 0; i < fullChars - 16; i += 16) {
				//	write(STDOUT_FILENO, bar, 16 * 3);
				//}
				//write(STDOUT_FILENO, bar, 3 * (fullChars - i));
				//write(STDOUT_FILENO, lastChar + 3 * lastCharIndex, 3);
				//write(STDOUT_FILENO, "\r", 1);

				////for (i = 0; i < fullChars - 16; i += 16) {
				////	printf("write(%d, %s, %d);\n", STDOUT_FILENO, bar, 16 * 3);
				////}
				////printf("write(%d, %s, %d);\n", STDOUT_FILENO, bar, 3 * (fullChars - i));
				////printf("write(%d, %s, %d);\n", STDOUT_FILENO, lastChar + 3 * lastCharIndex, 3);
				////printf("write(%d, %s, %d);\n", STDOUT_FILENO, "\r", 1);

				//vTaskDelay(10 / portTICK_PERIOD_MS);
				// Print delta

				//++cycles;
				////vTaskDelay(500 / portTICK_PERIOD_MS);
				//if (auto now = esp_timer_get_time(); now - last > 10000000) {
				//	double frac = (double)1000000 / (now - last);
				//	printf("%d cycles, %6.3f cycles/sec, %6.3f events/sec\n", cycles, (double)cycles * frac, (double)cycles * 180.0 / frac);
				//	last = now;
				//	cycles = 0;
				//}
			//} else {
				//ESP_LOGI(LOG_TAG, "waiting for connection");
				//suspend();
			}
		}

		//heap_caps_free(commandQueue);
	} catch(std::exception& e) {
		esp::loge("Caught exception: {}\nAborting.", e.what());
		abort();
	}
}
