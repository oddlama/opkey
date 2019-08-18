#pragma once

#include "sensor_history.h"
#include "entt.h"

#include <stdexcept>
#include <memory>
#include <array>


namespace OpKey {


class SensorManager {
public:
	inline static constexpr const size_t HistorySize = 5;

public:
	SensorManager() = default;

	SensorManager(const SensorManager&) = default;
	SensorManager(SensorManager&&) = default;
	SensorManager& operator=(const SensorManager&) = delete;
	SensorManager& operator=(SensorManager&&) = delete;

	auto& GetLogicStateChangeSink() noexcept { return logicStateChangeSink; }

private:
	SensorHistory<HistorySize> history{};

	entt::sigh<void(const SensorManager&, size_t sensor)> logicStateChangeSignal{};
	entt::sink<void(const SensorManager&, size_t sensor)> logicStateChangeSink{logicStateChangeSignal};
};


} // namespace OpKey
