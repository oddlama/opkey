#pragma once

#include "entt.h"


namespace OpKey {


class Application;

class Statistics {
public:
	Statistics(Application& application);

	Statistics(const Statistics&) = default;
	Statistics(Statistics&&) = default;
	Statistics& operator=(const Statistics&) = delete;
	Statistics& operator=(Statistics&&) = delete;

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

	void OnTick();

private:
	entt::scoped_connection onTickConnection;
};


} // namespace OpKey
