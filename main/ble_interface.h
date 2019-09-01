#pragma once

#include "ble_instance.h"

#include "entt.h"
#include "sensor.h"


namespace opkey {


namespace blecfg {

inline static std::array<uint8_t, 16> midiPacket{};

using namespace ble;
namespace co = ble::characteristic_options;

using MidiService = Service
	< Uuid128<0x03b80e5a, 0xede8, 0x0b33, 0x0751, 0xce34ec4c700>
	, Characteristic
		< Uuid128<0x7772e5db, 0x3868, 0x4112, 0xa1a9, 0xf2669d106bf3>
		//, co::BindVariable<&midiPacket>
		, co::Notify
		, co::WriteNoResponse
		, co::NoWriteAccess
		>
	>;

using Server = ble::Server<MidiService>;

} // namespace blecfg


class Application;
class SensorManager;

class BleInterface {
public:
	BleInterface(Application& application);

	BleInterface(const BleInterface&) = default;
	BleInterface(BleInterface&&) = default;
	BleInterface& operator=(const BleInterface&) = delete;
	BleInterface& operator=(BleInterface&&) = delete;

	void OnTick();
	void OnSensorStateChange(const SensorManager& sensorManager, Sensor sensor);

	//void OnKeyPressed(Key key, double velocity, ) {
	//}
	//void OnKeyReleased(Key key, ) {
	//}

private:
	entt::scoped_connection onTickConnection;
	entt::scoped_connection onSensorStateChangeConnection;

	ble::Instance<blecfg::Server> bleInstance{"OpKey"};
};


} // namespace opkey
