#pragma once

#include "ble_instance.h"

#include "entt.h"
#include "sensor.h"


namespace opkey {


namespace blecfg {

inline std::array<uint8_t, 32> midiPacket{};

using namespace ble;
namespace chr = ble::characteristic_options;
namespace svr = ble::server_options;

using MidiService = Service
	< Uuid128<0x03b80e5a, 0xede8, 0x4b33, 0xa751, 0x6ce34ec4c700>
	, Characteristic
		< Uuid128<0x7772e5db, 0x3868, 0x4112, 0xa1a9, 0xf2669d106bf3>
		, chr::BindVariable<&midiPacket>
		, chr::Notify
		, chr::WriteNoResponse
		>
	>;

//inline void OnConnect(const ble_gap_conn_desc& desc) {
//}
//
//inline void OnDisconnect(int reason, const ble_gap_conn_desc& desc) {
//}

using Server = ble::Server
	< MidiService
	, svr::AdvertiseUuid<MidiService::Uuid>
	//, svr::ConnectCallback<OnConnect>
	//, svr::DisconnectCallback<OnDisconnect>
	>;

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
