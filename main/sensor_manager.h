#pragma once

#include "adc_controller.h"
#include "mode.h"
#include "entt.h"

#include <stdexcept>
#include <memory>
#include <array>


namespace opkey {


class Application;

class SensorManager {
public:
	SensorManager(Application& application);

	SensorManager(const SensorManager&) = default;
	SensorManager(SensorManager&&) = default;
	SensorManager& operator=(const SensorManager&) = delete;
	SensorManager& operator=(SensorManager&&) = delete;

	const auto& GetLogicStates() const noexcept { return logicStates; }
	auto& GetOnSensorStateChangeSink() noexcept { return onSensorStateChangeSink; }

	void OnTick();
	void OnModeChange(Mode oldMode, Mode newMode);

	void InitLogicStates(SensorData& newData);
	void InitSingleSensorHistory();
	void CalculateNextSensorState(SensorData& newData);
	void CalculateNextSensorState(size_t rawIndex, double newData);

private:
	SensorLogicStateData logicStates{};
	std::array<uint16_t, config::singleSensorHistorySize> singleSensorHistory;

	AdcController adcController{};

	entt::scoped_connection onTickConnection;
	entt::scoped_connection onModeChangeConnection;
	entt::sigh<void(const SensorManager&, Sensor sensor)> onSensorStateChangeSignal{};
	entt::sink<void(const SensorManager&, Sensor sensor)> onSensorStateChangeSink{onSensorStateChangeSignal};
};


} // namespace opkey
