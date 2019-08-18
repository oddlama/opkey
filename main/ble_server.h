#pragma once


namespace OpKey {


class BleServer {
public:
	BleServer() noexcept = default;

	BleServer(const BleServer&) = default;
	BleServer(BleServer&&) = default;
	BleServer& operator=(const BleServer&) = delete;
	BleServer& operator=(BleServer&&) = delete;

	//void OnKeyPressed(Key key, double velocity, ) {
	//}
	//void OnKeyReleased(Key key, ) {
	//}

private:
};


} // namespace OpKey
