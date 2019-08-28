#include "fmt.h"
#include "ble_interface.h"
#include "ble.h"
#include "application.h"
#include "sensor_manager.h"


namespace opkey {


using MidiService = Service
	< Uuid128<0x03b80e5a, 0xede8, 0x0b33, 0x0751, 0xce34ec4c700>
	, Characteristic
		< Uuid128<0x7772e5db, 0x3868, 0x4112, 0xa1a9, 0xf2669d106bf3>
		, CharacteristicBindVariable<&midiPacket>
		, CharacteristicNotify
		//, CharacteristicIndicate
		//, CharacteristicNotifyOnSubscription
		//, CharacteristicIndicateOnSubscription
		//, CharacteristicNoWriteAccess
		//, CharacteristicNoReadAccess
		, CharacteristicWriteWithoutResponse
		>
	>;

using OpKeyGattServer = GattServer<MidiService>;

static std::array<uint8_t, 16> midiPacket{};


BleInterface::BleInterface(Application& application)
	: onTickConnection(application.GetOnTickSink().connect<&BleInterface::OnTick>(*this))
	, onSensorStateChangeConnection(application.GetOnSensorStateChangeSink().connect<&BleInterface::OnSensorStateChange>(*this))
{
	OpKeyGattServer gattServer{};
	GattServer server{};
	server.
	Ble::Init<OpKeyGattServer>("OpKey");
}

void BleInterface::OnTick() {
	OPKEY_PROFILE_FUNCTION();
}

void BleInterface::OnSensorStateChange(const SensorManager& sensorManager, Sensor sensor) {
	auto& t_0 = sensorManager.GetHistory()[0];
	auto& keyState = t_0.keyState[sensor];
	auto& keyPos = t_0.kinematic.position[sensor];
	auto& keyVel = t_0.kinematic.velocity[sensor];
	auto& keyAcc = t_0.kinematic.acceleration[sensor];
	if (keyState.pressed) {
		fmt::print("key[{:2d}] down  pos: {:7.2f} vel: {:7.2f} acc: {:7.2f}\n", static_cast<size_t>(sensor), keyPos, keyVel, keyAcc);
	} else {
		fmt::print("key[{:2d}] up    pos: {:7.2f} vel: {:7.2f} acc: {:7.2f}\n", static_cast<size_t>(sensor), keyPos, keyVel, keyAcc);
	}
}


} // namespace opkey
