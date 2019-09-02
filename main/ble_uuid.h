#pragma once

#include "fmt.h"
#include <host/ble_uuid.h>


namespace opkey::ble {


inline std::string ToString(const ble_uuid16_t& uuid) {
	return fmt::format("{:04x}", uuid.value);
}

inline std::string ToString(const ble_uuid32_t& uuid) {
	return fmt::format("{:08x}", uuid.value);
}

inline std::string ToString(const ble_uuid128_t& uuid) {
	return fmt::format("{:02x}{:02x}{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}"
		, uuid.value[15], uuid.value[14], uuid.value[13], uuid.value[12]
		, uuid.value[11], uuid.value[10], uuid.value[ 9], uuid.value[ 8]
		, uuid.value[ 7], uuid.value[ 6], uuid.value[ 5], uuid.value[ 4]
		, uuid.value[ 3], uuid.value[ 2], uuid.value[ 1], uuid.value[ 0]
		);
}

inline std::string ToString(const ble_uuid_t* uuid) {
	if (not uuid) {
		return "(null uuid)";
	}

	switch (uuid->type) {
		case BLE_UUID_TYPE_16:  return ToString(*reinterpret_cast<const ble_uuid16_t*>(static_cast<const void*>(uuid)));
		case BLE_UUID_TYPE_32:  return ToString(*reinterpret_cast<const ble_uuid32_t*>(static_cast<const void*>(uuid)));
		case BLE_UUID_TYPE_128: return ToString(*reinterpret_cast<const ble_uuid128_t*>(static_cast<const void*>(uuid)));
		default:                return "(invalid uuid type)";
	}
}


struct UuidTag { };

template<uint32_t A, uint16_t B, uint16_t C, uint16_t D, uint64_t E>
struct Uuid128 : private UuidTag {
	static_assert(E <= 0xffffffffffff, "Invalid service uuid128: Template argument 'E' is out of range");

	inline static constexpr const std::array<uint8_t, 16> bytes =
		{ static_cast<uint8_t>(E >>  0)
		, static_cast<uint8_t>(E >>  8)
		, static_cast<uint8_t>(E >> 16)
		, static_cast<uint8_t>(E >> 24)
		, static_cast<uint8_t>(E >> 32)
		, static_cast<uint8_t>(E >> 40)
		, static_cast<uint8_t>(D >>  0)
		, static_cast<uint8_t>(D >>  8)
		, static_cast<uint8_t>(C >>  0)
		, static_cast<uint8_t>(C >>  8)
		, static_cast<uint8_t>(B >>  0)
		, static_cast<uint8_t>(B >>  8)
		, static_cast<uint8_t>(A >>  0)
		, static_cast<uint8_t>(A >>  8)
		, static_cast<uint8_t>(A >> 16)
		, static_cast<uint8_t>(A >> 24)
		};

private:
	inline static constexpr const ble_uuid128_t ToNimbleUuid() noexcept {
		ble_uuid128_t ret{};
		ret.u.type = BLE_UUID_TYPE_128;
		for (int i = 0; i < 16; ++i) {
			ret.value[i] = bytes[i];
		}
		return ret;
	};

public:
	inline static constexpr const ble_uuid128_t nimbleUuid = ToNimbleUuid();

	inline static constexpr uint16_t As16Bit() noexcept {
		return static_cast<uint16_t>(A);
	}

	inline static std::string ToString() {
		return fmt::format("{:08x}-{:04x}-{:04x}-{:04x}-{:012x}", A, B, C, D, E);
	}
};

template<uint16_t A>
struct Uuid16 : private UuidTag {
	inline static constexpr const std::array<uint8_t, 2> bytes =
		{ static_cast<uint8_t>(A >> 0)
		, static_cast<uint8_t>(A >> 8)
		};

private:
	inline static constexpr const ble_uuid16_t ToNimbleUuid() noexcept {
		ble_uuid16_t ret{};
		ret.u.type = BLE_UUID_TYPE_16;
		ret.value = A;
		return ret;
	};

public:
	inline static constexpr const ble_uuid16_t nimbleUuid = ToNimbleUuid();

	inline static constexpr uint16_t As16Bit() noexcept {
		return A;
	}

	inline static std::string ToString() {
		return fmt::format("{:08x}", A);
	}
};

struct BluetoothBaseUuid
	: public Uuid128<0x00000000, 0x0000, 0x1000, 0x8000, 0x00805f9b34fb>
{
	template<uint16_t A>
	using From16Bit = Uuid128<A, 0x0000, 0x1000, 0x8000, 0x00805f9b34fb>;
};

struct UuidAuto : private UuidTag {
private:
	// TODO implement auto uuids
	struct AutoUuidIsNotYetImplemented {
		void operator&() { }
	};

public:
	inline static constexpr const AutoUuidIsNotYetImplemented nimbleUuid{};
};


} // namespace opkey::ble
