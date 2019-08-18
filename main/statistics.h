#pragma once


namespace OpKey {


class Statistics {
public:
	Statistics() noexcept = default;

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

private:
};


} // namespace OpKey
