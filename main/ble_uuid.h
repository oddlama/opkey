#pragma once


namespace opkey::ble {


struct UuidTag { };

template<uint32_t A, uint16_t B, uint16_t C, uint16_t D, uint64_t E>
struct Uuid128 : private UuidTag {
	static_assert(E <= 0xffffffffffff, "Invalid service uuid128: Template argument 'E' is out of range");

	inline constexpr static const std::array<uint8_t, 16> Bytes =
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

	constexpr static uint16_t As16Bit() noexcept {
		return static_cast<uint16_t>(A);
	};
};

template<uint16_t A>
struct Uuid16 : private UuidTag {
	inline constexpr static const std::array<uint8_t, 2> Bytes =
		{ static_cast<uint8_t>(A >> 0)
		, static_cast<uint8_t>(A >> 8)
		};

	constexpr static uint16_t As16Bit() noexcept {
		return A;
	};
};

struct BluetoothBaseUuid
	: public Uuid128<0x00000000, 0x0000, 0x1000, 0x8000, 0x00805f9b34fb>
{
	template<uint16_t A>
	using From16Bit = Uuid128<A, 0x0000, 0x1000, 0x8000, 0x00805f9b34fb>;
};

struct UuidAuto : private UuidTag { };


} // namespace opkey::ble
