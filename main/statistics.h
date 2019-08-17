#pragma once


namespace OpKey {


class Application;

class Statistics {
public:
	explicit Statistics(Application& application) noexcept
		: application(application)
	{ }

	Statistics(const Statistics&) = delete;
	Statistics(Statistics&&) = delete;
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

private:
	Application& application;
};


} // namespace OpKey
