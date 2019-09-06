#pragma once

#include "ble_meta.h"
#include "ble_uuid.h"
#include "ble_array.h"

#include <host/ble_gatt.h>
#include <os/os_mbuf.h>


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

	struct ReadHandlerTag         { };
	struct WriteHandlerTag        { };
	struct SubscriptionHandlerTag { };

	template<auto V>
	struct FixedValue
		: private CharacteristicMixinTag
		, private ReadHandlerTag
	{
		static inline constexpr const auto value = V;

		static int OnRead(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context) {
			int err = os_mbuf_append(context->om, &value, sizeof(value));
			return err == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
		}
	};

	template<auto* Function>
	struct ReadCallback
		: private CharacteristicMixinTag
		, private ReadHandlerTag
	{
		static int OnRead(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context) {
			return Function(connHandle, attrHandle, context);
		}
	};

	template<auto* Function>
	struct WriteCallback
		: private CharacteristicMixinTag
		, private WriteHandlerTag
	{
		static int OnWrite(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context) {
			return Function(connHandle, attrHandle, context);
		}
	};

	template<auto* SendArrayPtr, auto* RecvArrayPtr = SendArrayPtr>
	struct BindArray
		: private CharacteristicMixinTag
		, private std::conditional_t<SendArrayPtr == nullptr, struct MissingSendArrayPtr, ReadHandlerTag>
		, private std::conditional_t<RecvArrayPtr == nullptr, struct MissingRecvArrayPtr, WriteHandlerTag>
	{
	private:
		using TSendArrayPtr = std::decay_t<std::remove_pointer_t<decltype(SendArrayPtr)>>;
		using TRecvArrayPtr = std::decay_t<std::remove_pointer_t<decltype(RecvArrayPtr)>>;
		static_assert(std::is_same_v<std::nullptr_t, TSendArrayPtr> || std::is_base_of_v<ArrayTag, TSendArrayPtr>, "BindArray (SendArrayPtr) can only be used in conjunction with ble::Array variables");
		static_assert(std::is_same_v<std::nullptr_t, TRecvArrayPtr> || std::is_base_of_v<ArrayTag, TRecvArrayPtr>, "BindArray (RecvArrayPtr) can only be used in conjunction with ble::Array variables");

	public:
		static int OnRead(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context) {
			int err = os_mbuf_append(context->om, SendArrayPtr->data(), SendArrayPtr->GetUsedSize());
			return err == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
		}

		static int OnWrite(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context) {
			if (OS_MBUF_PKTLEN(context->om) > RecvArrayPtr->size()) {
				return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
			}

			uint16_t countCopied;
			int err = ble_hs_mbuf_to_flat(context->om, RecvArrayPtr->data(), RecvArrayPtr->size(), &countCopied);
			RecvArrayPtr->SetUsedSize(countCopied);
			return err == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
		}
	};

	template<auto* VariablePtr>
	struct BindVariable
		: private CharacteristicMixinTag
		, private ReadHandlerTag
		, private WriteHandlerTag
	{
		static int OnRead(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context) {
			int err = os_mbuf_append(context->om, VariablePtr, sizeof(*VariablePtr));
			return err == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
		}

		static int OnWrite(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context) {
			if (OS_MBUF_PKTLEN(context->om) != sizeof(*VariablePtr)) {
				return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
			}

			uint16_t countCopied;
			int err = ble_hs_mbuf_to_flat(context->om, VariablePtr, sizeof(*VariablePtr), &countCopied);
			return err == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
		}
	};

	struct IndicateOnSubscribe
		: private CharacteristicMixinTag
		, private SubscriptionHandlerTag
	{
		template<typename InstanceType, typename Characteristic>
		static int OnSubscribe(uint16_t connHandle, uint8_t reason,
			bool prevNotify, bool curNotify, bool prevIndicate, bool curIndicate)
		{
			InstanceType::Indicate(connHandle, Characteristic::valHandle);
			return 0;
		}
	};

	struct NotifyOnSubscribe
		: private CharacteristicMixinTag
		, private SubscriptionHandlerTag
	{
		template<typename InstanceType, typename Characteristic>
		static int OnSubscribe(uint16_t connHandle, uint8_t reason,
			bool prevNotify, bool curNotify, bool prevIndicate, bool curIndicate)
		{
			InstanceType::Notify(connHandle, Characteristic::valHandle);
			return 0;
		}
	};
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

	using Uuid = meta::GetDerivedType<UuidTag, UuidAuto, Options...>;

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

	static_assert((not writeNoResponse) || (not noWriteAccess), "WriteNoResponse requires write access");

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
	static_assert(readHandlerCount <= 1, "Multiple read handlers are not supported");
	static_assert(writeHandlerCount <= 1, "Multiple write handlers are not supported");
	static_assert(subscriptionHandlerCount <= 1, "Multiple subscription handlers are not supported");

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

	static inline uint16_t valHandle = 0;

	constexpr static ble_gatt_chr_def NimbleCharacteristicDefinition() noexcept {
		return
			{ // .uuid
				reinterpret_cast<const ble_uuid_t*>(&Uuid::nimbleUuid)
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
				&valHandle
			};
	}

	template<typename InstanceType>
	static void OnSubscribe(uint16_t connHandle, uint8_t reason,
			bool prevNotify, bool curNotify, bool prevIndicate, bool curIndicate)
	{
		if constexpr (hasSubscriptionHandler) {
			SubscriptionHandler::template OnSubscribe<InstanceType, Characteristic>(connHandle,
					reason, prevNotify, curNotify, prevIndicate, curIndicate);
		}

		// Suppress usage warnings due to constexpr branches
		(void)connHandle;
		(void)reason;
		(void)prevNotify;
		(void)curNotify;
		(void)prevIndicate;
		(void)curIndicate;
	}

private:
	static int NimbleOnAccess(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context, void* arg) {
		switch (context->op) {
			case BLE_GATT_ACCESS_OP_READ_CHR:
				if constexpr (hasReadHandler) {
					return ReadHandler::OnRead(connHandle, attrHandle, context);
				} else {
					return BLE_ATT_ERR_UNLIKELY;
				}

			case BLE_GATT_ACCESS_OP_WRITE_CHR:
				if constexpr (hasWriteHandler) {
					return WriteHandler::OnWrite(connHandle, attrHandle, context);
				} else {
					return BLE_ATT_ERR_UNLIKELY;
				}

			default:
			case BLE_GATT_ACCESS_OP_READ_DSC:
			case BLE_GATT_ACCESS_OP_WRITE_DSC:
				return BLE_ATT_ERR_UNLIKELY;
		}

		// Suppress usage warnings due to constexpr branches
		(void)connHandle;
		(void)attrHandle;

		return BLE_ATT_ERR_UNLIKELY;
	}
};


} // namespace opkey::ble
