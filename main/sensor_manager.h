#pragma once

#include "sensor_history.h"
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
	inline static constexpr const size_t HistorySize = 3;

public:
	SensorManager(Application& application);

	SensorManager(const SensorManager&) = default;
	SensorManager(SensorManager&&) = default;
	SensorManager& operator=(const SensorManager&) = delete;
	SensorManager& operator=(SensorManager&&) = delete;

	const auto& GetHistory() const noexcept { return history; }
	auto& GetOnSensorStateChangeSink() noexcept { return onSensorStateChangeSink; }

	void OnTick();
	void OnModeChange(Mode oldMode, Mode newMode);

	void InitHistory(SensorData& newData);
	void CalculateNextSensorState(SensorData& newData);

private:
	SensorHistory<HistorySize> history{};
	AdcController adcController{};

	entt::scoped_connection onTickConnection;
	entt::scoped_connection onModeChangeConnection;
	entt::sigh<void(const SensorManager&, Sensor sensor)> onSensorStateChangeSignal{};
	entt::sink<void(const SensorManager&, Sensor sensor)> onSensorStateChangeSink{onSensorStateChangeSignal};
};


} // namespace opkey
