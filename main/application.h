#pragma once

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#include <Task.h>

#include "mcp3208.h"

class Application
	: public Task
	, public BLEServerCallbacks
{
public:
	Application() noexcept
		: Task("pctMain", 8192)
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
	void BLEInit();

private:
	bool deviceConnected = false;
	BLECharacteristic* characteristic = nullptr;
	Mcp3208 mcp{};
};
