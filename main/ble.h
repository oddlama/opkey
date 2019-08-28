#pragma once

#include "ble_meta.h"
#include "ble_uuid.h"


namespace opkey::ble {


struct CharacteristicMixinTag { };


namespace characteristic_properties {
	struct NoReadAccess    : private CharacteristicMixinTag { };
	struct NoWriteAccess   : private CharacteristicMixinTag { };
	struct WriteNoResponse : private CharacteristicMixinTag { };
	struct Notify          : private CharacteristicMixinTag { };
	struct Indicate        : private CharacteristicMixinTag { };

	template<auto Value>
	struct FixedValue : private Read, private Write {
	};

	template<auto* VariablePtr>
	struct BindVariable {
	};
};


struct CharacteristicTag { } ;

template<typename Options...>
struct Characteristic : private CharacteristicTag {
	static_assert(meta::CountDerivedType<UuidTag, Options...> <= 1, "Characteristic must not include more than one Uuid");
	static_assert(meta::CountDerivedType<ReadHandlerTag, Options...> <= 1, "Characteristic must not include more than one ReadHandler");
	static_assert(meta::CountDerivedType<WriteHandlerTag, Options...> <= 1, "Characteristic must not include more than one WriteHandler");
	static_assert(
			meta::CountDerivedType<UuidTag, Options...> +
			meta::CountDerivedType<CharacteristicMixinTag, Options...> ==
				sizeof...(Options)
			, "Characteristic definition contains an invalid type"
			);

	using UuidType = meta::GetDerivedType<UuidTag, UuidAuto, Options...>;

	static inline constexpr const bool NoReadAccess    = meta::HasType<characteristic_properties::NoReadAccess,    Options...>;
	static inline constexpr const bool NoWriteAccess   = meta::HasType<characteristic_properties::NoWriteAccess,   Options...>;
	static inline constexpr const bool WriteNoResponse = meta::HasType<characteristic_properties::WriteNoResponse, Options...>;
	static inline constexpr const bool Notify          = meta::HasType<characteristic_properties::Notify,          Options...>;
	static inline constexpr const bool Indicate        = meta::HasType<characteristic_properties::Indicate,        Options...>;

	static inline constexpr const uint8_t NimbleGattChrPropValue = 0
		| (NoReadAccess    ? 0                                  : BLE_GATT_CHR_PROP_READ)
		| (NoWriteAccess   ? 0                                  : BLE_GATT_CHR_PROP_WRITE)
		| (WriteNoResponse ? BLE_GATT_CHR_PROP_WRITE_NO_RSP     : 0)
		| (Notify          ? BLE_GATT_CHR_PROP_NOTIFY           : 0)
		| (Indicate        ? BLE_GATT_CHR_PROP_INDICATE         : 0)
		;

	static inline constexpr const bool HasReadHandler = ;
	static inline constexpr const bool HasWriteHandler = ;
	static inline constexpr const bool HasSubscriptionHandler = ;
	//using ReadHandler = ;
	//using WriteHandler = ;
	//using SubscriptionHandler = ;

	// If there is read access, a read handler must exist
	static_assert(NoReadAccess || HasReadHandler, "Characteristic has read access, but no read handler");
	// If there is write access, a write handler must exist
	static_assert(NoWriteAccess || HasWriteHandler, "Characteristic has write access, but no write handler");
	// If a subscription handler exists, there must be read access.
	static_assert((not HasSubscriptionHandler) || (not NoReadAccess), "Characteristic has subscription handler, but no read access");
};


struct ServiceTag { };

template<typename Uuid, typename... Options>
struct Service : private ServiceTag {
	static_assert(meta::CountDerivedType<UuidTag, Options...> <= 1, "Service must not include more than one Uuid");
	static_assert(
			meta::CountDerivedType<UuidTag, Options...> +
			meta::CountDerivedType<CharacteristicTag, Options...> ==
				sizeof...(Options)
			, "Service definition contains an invalid type"
			);

	using UuidType = meta::GetDerivedType<UuidTag, UuidAuto, Options...>;
	using CharacteristicTuple = ExtractDerivedTypes<CharacteristicTag, Options...>;
};


struct ServerMixinTag { };
struct ServerConnectCallbackTag : private ServerMixinTag { };
struct ServerDisconnectCallbackTag : private ServerMixinTag { };

template<typename F>
struct ServerConnectCallback : private ServerConnectCallbackTag { };

template<typename F>
struct ServerDisconnectCallback : private ServerDisconnectCallbackTag { };


struct ServerTag { };

template<typename... Options>
struct Server : private ServerTag {
	static_assert(
			meta::CountDerivedType<ServiceMixinTag, Options...> +
			meta::CountDerivedType<ServiceTag, Options...> ==
				sizeof...(Options)
			, "Server definition contains an invalid type"
			);

	using UuidType = meta::GetDerivedType<UuidTag, UuidAuto, Options...>;
	using ServiceTuple = ExtractDerivedTypes<ServiceTag, Options...>;
	static constexpr const size_t ServiceCount = std::tuple_size_v<ServiceTuple>;

	static constexpr const std::array<ble_gatt_svc_def, ServiceCount + 1> gattServiceDefinitions = {
		(..., Service),
		gattServiceSentinel
	};
};


static_assert(ESP_OK == 0, "This module relies on the value of ESP_OK to be 0");


static void Init(const char* name);


} // namespace opkey::ble
