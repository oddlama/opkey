#pragma once

#include "sk6812.h"


namespace OpKey {


class Application;

class Visualizer {
public:
	explicit Visualizer(Application& application) noexcept
		: application(application)
	{ }

	Visualizer(const Visualizer&) = delete;
	Visualizer(Visualizer&&) = delete;
	Visualizer& operator=(const Visualizer&) = delete;
	Visualizer& operator=(Visualizer&&) = delete;

	//void OnKeyPressed(Key key, double velocity, ) {
	//	invalid = true;
	//}
	//void OnKeyReleased(Key key, ) {
	//	invalid = true;
	//}
	//void Tick() {
	//	if (invalid || lastUpdate - now > updateDelayOrFrequencyOrSo) {
	//		invalid = false;

	//		show();
	//	}
	//}

private:
	Application& application;
};


} // namespace OpKey
