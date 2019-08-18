#pragma once

#include "entt.h"


namespace OpKey {


class Application;

class BleServer {
public:
	BleServer(Application& application);

	BleServer(const BleServer&) = default;
	BleServer(BleServer&&) = default;
	BleServer& operator=(const BleServer&) = delete;
	BleServer& operator=(BleServer&&) = delete;

	void OnTick();

	//void OnKeyPressed(Key key, double velocity, ) {
	//}
	//void OnKeyReleased(Key key, ) {
	//}

private:
	entt::scoped_connection tickConnection;
};


} // namespace OpKey
