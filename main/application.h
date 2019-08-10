#pragma once

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <WS2812.h>
#include <Task.h>

#include "spi_host.h"
#include "spi_device.h"
#include "ads7953.h"



namespace OpKey {


class Application
	: public Task
	, public BLEServerCallbacks
{
	enum class Mode {
		Run,
		Calibrate
	};

public:
	Application() noexcept
		: Task("OpKey", 8192)
		, BLEServerCallbacks()
	{ }

	Application(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;

	using BLEServerCallbacks::onConnect;
	void onConnect(BLEServer* pServer) override;
	void onDisconnect(BLEServer* pServer) override;
	void run(void*) override { (*this)(); }

private:
	void operator()();
	void InitBle();
	void InitSpi();
	void InitAdcs();

	void Run();
	void RunStatistics();
	void Calibrate();

private:
	// BLE
	bool deviceConnected = false;
	BLECharacteristic* characteristic = nullptr;

	// Statistics
	std::chrono::steady_clock::time_point lastStatisticPrint{};
	uint32_t operationCounter = 0;
	uint32_t bleEventCounter = 0;

	// Mode and settings
	Mode mode = Mode::Run;
	size_t multisamples = Config::DefaultMultisamples;

	// Spi
	SpiHost hspi{};
	SpiHost vspi{};
	std::array<SpiDevice, Config::NumAdcs> adcs{};

	// Leds
	WS2812 ws2812{GPIO_NUM_32, 143};
};


} // namespace OpKey
