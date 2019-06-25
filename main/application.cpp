#include <cmath>
#include <array>

#include <driver/adc.h>
#include <esp_adc_cal.h>
#include <esp_log.h>

#include "application.h"

static const char* LOG_TAG = "PctApp";

#define SERVICE_UUID        "03b80e5a-ede8-4b33-a751-6ce34ec4c700"
#define CHARACTERISTIC_UUID "7772e5db-3868-4112-a1a9-f2669d106bf3"


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
	ESP_LOGI(LOG_TAG, "init BLE");
	BLEDevice::init("PCTMidi");

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
	//setvbuf(stdout, NULL, _IONBF, 0);
	BLEInit();

	std::array<Mcp3208::Command, 8> readChannel{};
	for (int c = 0; c < 8; ++c) {
		readChannel[c] = Mcp3208::Command(c, false);
	}

	Mcp3208::Command* commandQueue = (Mcp3208::Command*)heap_caps_malloc(sizeof(Mcp3208::Command) * 100, MALLOC_CAP_DMA);
	auto Sample100 = [&](int c) {
		int ival = 0;
		for (int i = 0; i < 100; ++i) {
			commandQueue[i] = readChannel[c];
		}
		Mcp3208::Command::Execute(mcp, commandQueue, 100);
		for (int i = 0; i < 100; ++i) {
			ival += commandQueue[i].GetValue();
		}
		return ival / 100;
	};

	while (true) {
		static unsigned long last = 0;
		//static uint32_t cycles = 0;
		if (deviceConnected) {
		} else {
			auto ReadCh = [&](int c) {
				int multisample = 1000;//00;
				int ival = 0;
				for (int i = 0; i < multisample; ++i) {
					ival += Sample100(c);
					//ival += mcp.Read(readChannel[c]);
				}
				double val = static_cast<double>(ival) / multisample;
				return val;
			};
			for (int c = 0; c < 8; ++c) {
				printf("%6.1f (c%d), ", ReadCh(c), c);
			}
			printf("\n");
			auto now = esp_timer_get_time();
			double frac = 1000000.0 / (now - last);
			printf("%6.3f ksps (800k in %7.3f sec) multisample per sensor at 480 Hz: %6.3f sps\n", 800.0 * frac, 1.0 / frac, 8000.0 / 9.0 / 48 * frac);
			last = now;
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

			//const int adcSteps = 4096;

			//int multisample = 64;
			//int ival = 0;
			//for (int i = 0; i < multisample; ++i) {
			//	ival += adc1_get_raw(ADC1_CHANNEL_0);
			//}
			//double val = (double)ival / multisample;

			//static double lastVal = 0.0;
			//// to distance
			//val = sqrt(val);
			//double diff = val - lastVal;
			//lastVal = val;

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

			//vTaskDelay(100 / portTICK_PERIOD_MS);
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

	heap_caps_free(commandQueue);
}
