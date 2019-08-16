#pragma once


namespace OpKey {


class Application;

class BleServer {
public:
	explicit BleServer(Application& application) noexcept
		: application(application)
	{ }

	BleServer(const BleServer&) = delete;
	BleServer(BleServer&&) = delete;
	BleServer& operator=(const BleServer&) = delete;
	BleServer& operator=(BleServer&&) = delete;

	//void OnKeyPressed(Key key, double velocity, ) {
	//}
	//void OnKeyReleased(Key key, ) {
	//}

private:
	Application& application;
};


} // namespace OpKey
