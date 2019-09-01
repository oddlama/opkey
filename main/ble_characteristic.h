#pragma once

#include "ble_meta.h"
#include "ble_uuid.h"

#include <host/ble_gatt.h>


namespace opkey::ble {


struct CharacteristicMixinTag { };

namespace characteristic_options {
	struct NoReadAccess       : private CharacteristicMixinTag { };
	struct NoWriteAccess      : private CharacteristicMixinTag { };
	struct ReadEncrypted      : private CharacteristicMixinTag { };
	struct ReadAuthenticated  : private CharacteristicMixinTag { };
	struct ReadAuthorized     : private CharacteristicMixinTag { };
	struct WriteEncrypted     : private CharacteristicMixinTag { };
	struct WriteAuthenticated : private CharacteristicMixinTag { };
	struct WriteAuthorized    : private CharacteristicMixinTag { };
	struct WriteNoResponse    : private CharacteristicMixinTag { };
	struct Notify             : private CharacteristicMixinTag { };
	struct Indicate           : private CharacteristicMixinTag { };

	struct FixedValueTag      : private CharacteristicMixinTag { };
	struct BindVariableTag    : private CharacteristicMixinTag { };
	struct AccessCallbackTag  : private CharacteristicMixinTag { };

	struct ReadHandlerTag         : private CharacteristicMixinTag { };
	struct WriteHandlerTag        : private CharacteristicMixinTag { };
	struct SubscriptionHandlerTag : private CharacteristicMixinTag { };

	template<auto Value>
	struct FixedValue : private FixedValueTag { };

	template<auto* VariablePtr>
	struct BindVariable : private BindVariableTag { };

	template<typename T>
	struct AccessCallback : private AccessCallbackTag { };
} // namespace characteristic_options


struct CharacteristicTag { };

template<typename... Options>
struct Characteristic : private CharacteristicTag {
	static_assert(meta::CountDerivedType<UuidTag, Options...> <= 1, "Characteristic must not include more than one Uuid");
	static_assert(meta::CountDerivedType<characteristic_options::ReadHandlerTag, Options...> <= 1, "Characteristic must not include more than one ReadHandler");
	static_assert(meta::CountDerivedType<characteristic_options::WriteHandlerTag, Options...> <= 1, "Characteristic must not include more than one WriteHandler");
	static_assert(
			meta::CountDerivedType<UuidTag, Options...> +
			meta::CountDerivedType<CharacteristicMixinTag, Options...> ==
				sizeof...(Options)
			, "Characteristic definition contains an invalid type"
			);

	using UuidType = meta::GetDerivedType<UuidTag, UuidAuto, Options...>;

	static inline constexpr const bool noReadAccess       = meta::HasType<characteristic_options::NoReadAccess,       Options...>;
	static inline constexpr const bool noWriteAccess      = meta::HasType<characteristic_options::NoWriteAccess,      Options...>;
	static inline constexpr const bool readEncrypted      = meta::HasType<characteristic_options::ReadEncrypted,      Options...>;
	static inline constexpr const bool readAuthenticated  = meta::HasType<characteristic_options::ReadAuthenticated,  Options...>;
	static inline constexpr const bool readAuthorized     = meta::HasType<characteristic_options::ReadAuthorized,     Options...>;
	static inline constexpr const bool writeEncrypted     = meta::HasType<characteristic_options::WriteEncrypted,     Options...>;
	static inline constexpr const bool writeAuthenticated = meta::HasType<characteristic_options::WriteAuthenticated, Options...>;
	static inline constexpr const bool writeAuthorized    = meta::HasType<characteristic_options::WriteAuthorized,    Options...>;
	static inline constexpr const bool writeNoResponse    = meta::HasType<characteristic_options::WriteNoResponse,    Options...>;
	static inline constexpr const bool notify             = meta::HasType<characteristic_options::Notify,             Options...>;
	static inline constexpr const bool indicate           = meta::HasType<characteristic_options::Indicate,           Options...>;

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

	static inline constexpr const size_t readHandlerCount = meta::CountDerivedType<characteristic_options::ReadHandlerTag, Options...>;
	static inline constexpr const size_t writeHandlerCount = meta::CountDerivedType<characteristic_options::WriteHandlerTag, Options...>;
	static inline constexpr const size_t subscriptionHandlerCount = meta::CountDerivedType<characteristic_options::SubscriptionHandlerTag, Options...>;

	static inline constexpr const bool hasReadHandler = readHandlerCount > 0;
	static inline constexpr const bool hasWriteHandler = writeHandlerCount > 0;
	static inline constexpr const bool hasSubscriptionHandler = subscriptionHandlerCount > 0;
	using ReadHandler = meta::GetDerivedType<characteristic_options::ReadHandlerTag, struct NoReadHandler, Options...>;
	using WriteHandler = meta::GetDerivedType<characteristic_options::WriteHandlerTag, struct NoWriteHandler, Options...>;
	using SubscriptionHandler = meta::GetDerivedType<characteristic_options::SubscriptionHandlerTag, struct NoSubscriptionHandler, Options...>;

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
		return 0;
	}
};


} // namespace opkey::ble
