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
	struct FixedValue : private CharacteristicMixinTag {
	};

	template<auto* VariablePtr>
	struct BindVariable : private CharacteristicMixinTag {
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

	static inline constexpr const bool noReadAccess       = meta::HasType<characteristic_properties::NoReadAccess,       Options...>;
	static inline constexpr const bool noWriteAccess      = meta::HasType<characteristic_properties::NoWriteAccess,      Options...>;
	static inline constexpr const bool readEncrypted      = meta::HasType<characteristic_properties::ReadEncrypted,      Options...>;
	static inline constexpr const bool readAuthenticated  = meta::HasType<characteristic_properties::ReadAuthenticated,  Options...>;
	static inline constexpr const bool readAuthorized     = meta::HasType<characteristic_properties::ReadAuthorized,     Options...>;
	static inline constexpr const bool writeEncrypted     = meta::HasType<characteristic_properties::WriteEncrypted,     Options...>;
	static inline constexpr const bool writeAuthenticated = meta::HasType<characteristic_properties::WriteAuthenticated, Options...>;
	static inline constexpr const bool writeAuthorized    = meta::HasType<characteristic_properties::WriteAuthorized,    Options...>;
	static inline constexpr const bool writeNoResponse    = meta::HasType<characteristic_properties::WriteNoResponse,    Options...>;
	static inline constexpr const bool notify             = meta::HasType<characteristic_properties::Notify,             Options...>;
	static inline constexpr const bool indicate           = meta::HasType<characteristic_properties::Indicate,           Options...>;

	static inline constexpr const ble_gatt_chr_flags nimbleChrFlagsValue = 0
		| (noReadAccess       ? 0                               : BLE_GATT_CHR_F_READ)
		| (noWriteAccess      ? 0                               : BLE_GATT_CHR_F_WRITE)
		| (readEncrypted      ? BLE_GATT_CHR_F_READ_ENC         : 0)
		| (readAuthenticated  ? BLE_GATT_CHR_F_READ_AUTHEN      : 0)
		| (readAuthorized     ? BLE_GATT_CHR_F_READ_AUTHOR      : 0)
		| (writeEncrypted     ? BLE_GATT_CHR_F_WRITE_ENC        : 0)
		| (writeAuthenticated ? BLE_GATT_CHR_F_WRITE_AUTHEN     : 0)
		| (writeAuthorized    ? BLE_GATT_CHR_F_WRITE_AUTHOR     : 0)
		| (writeNoResponse    ? BLE_GATT_CHR_F_WRITE_NO_RSP     : 0)
		| (notify             ? BLE_GATT_CHR_F_NOTIFY           : 0)
		| (indicate           ? BLE_GATT_CHR_F_INDICATE         : 0)
		;

	static inline constexpr const bool hasReadHandler = ;
	static inline constexpr const bool hasWriteHandler = ;
	static inline constexpr const bool hasSubscriptionHandler = ;
	//using ReadHandler = ;
	//using WriteHandler = ;
	//using SubscriptionHandler = ;

	// If there is read access, a read handler must exist
	static_assert(noReadAccess || hasReadHandler, "Characteristic has read access, but no read handler");
	// If there is write access, a write handler must exist
	static_assert(noWriteAccess || hasWriteHandler, "Characteristic has write access, but no write handler");
	// If a subscription handler exists, there must be read access.
	static_assert((not hasSubscriptionHandler) || (not noReadAccess), "Characteristic has subscription handler, but no read access");

	constexpr static ble_gatt_chr_def NimbleCharacteristicDefinition() noexcept {
		return
			{ // .uuid
				&UuidType::nimbleUuid
			, // .access_cb
				&NimbleOnAccess
			, // .arg
				nullptr
			, // .descriptors
				nullptr
			, // .flags
				nimbleChrFlagsValue
			, // .min_key_size
				0
			, // .val_handle
				nullptr
			};
	}

private:
	static int NimbleOnAccess(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context, void* arg) {
	}
};


} // namespace opkey::ble
