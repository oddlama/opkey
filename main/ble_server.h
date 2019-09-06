#pragma once

#include "ble_meta.h"
#include "ble_uuid.h"
#include "ble_service.h"

#include <host/ble_gap.h>


namespace opkey::ble {


struct ServerMixinTag { };

namespace server_options {

struct ConnectHandlerTag { };
struct DisconnectHandlerTag { };
struct AdvertiseUuidTag { };

template<auto Func>
struct ConnectCallback
	: private ServerMixinTag
	, private ConnectHandlerTag
{
	static void OnConnect(const ble_gap_conn_desc& desc) {
		Func(desc);
	}
};

template<auto Func>
struct DisconnectCallback
	: private ServerMixinTag
	, private DisconnectHandlerTag
{
	static void OnDisconnect(int reason, const ble_gap_conn_desc& desc) {
		Func(reason, desc);
	}
};

template<typename UuidType>
struct AdvertiseUuid
	: private ServerMixinTag
	, private AdvertiseUuidTag
{
	using Uuid = UuidType;
};

} // namespace server_options


template<typename Tuple>
struct ExpandServiceDefinitions;

template<typename... Ts>
struct ExpandServiceDefinitions<std::tuple<Ts...>> {
	static inline constexpr const std::array<ble_gatt_svc_def, sizeof...(Ts) + 1> value =
		{ Ts::NimbleServiceDefinition()...
		, { 0, nullptr, nullptr, nullptr }
		};
};


struct ServerTag { };

template<typename... Options>
struct Server : private ServerTag {
	static_assert(
			meta::CountDerivedType<ServerMixinTag, Options...> +
			meta::CountDerivedType<ServiceTag, Options...> ==
				sizeof...(Options)
			, "Server definition contains an invalid type"
			);

	static inline constexpr const size_t connectHandlerCount = meta::CountDerivedType<server_options::ConnectHandlerTag, Options...>;
	static inline constexpr const size_t disconnectHandlerCount = meta::CountDerivedType<server_options::DisconnectHandlerTag, Options...>;
	static inline constexpr const size_t advertiseUuidCount = meta::CountDerivedType<server_options::AdvertiseUuidTag, Options...>;
	static_assert(connectHandlerCount <= 1, "Multiple connect handlers are not supported");
	static_assert(disconnectHandlerCount <= 1, "Multiple disconnect handlers are not supported");
	static_assert(advertiseUuidCount <= 1, "Multiple uuid adverisements are not supported");

	static inline constexpr const bool hasConnectHandler = connectHandlerCount > 0;
	static inline constexpr const bool hasDisconnectHandler = disconnectHandlerCount > 0;
	static inline constexpr const bool hasAdvertiseUuid = advertiseUuidCount > 0;
	using ConnectHandler = meta::GetDerivedType<server_options::ConnectHandlerTag, struct NoConnectHandler, Options...>;
	using DisconnectHandler = meta::GetDerivedType<server_options::DisconnectHandlerTag, struct NoDisconnectHandler, Options...>;
	using AdvertiseUuid = meta::GetDerivedType<server_options::AdvertiseUuidTag, struct NoAdvertiseUuid, Options...>;

	using ServiceTuple = meta::ExtractDerivedTypes<ServiceTag, Options...>;
	static inline constexpr const auto nimbleGattServiceDefinitions =
		ExpandServiceDefinitions<ServiceTuple>::value;

	template<typename Uuid, typename ElseType = void>
	using GetTypeByUuid = meta::GetTypeByMixin<Uuid, ElseType, Server>;

	static void OnConnect(const ble_gap_conn_desc& desc) {
		if constexpr (hasConnectHandler) {
			ConnectHandler::OnConnect(desc);
		} else {
			(void)desc;
		}
	}

	static void OnDisconnect(int reason, const ble_gap_conn_desc& desc) {
		if constexpr (hasDisconnectHandler) {
			DisconnectHandler::OnDisconnect(reason, desc);
		} else {
			(void)reason;
			(void)desc;
		}
	}

	template<typename InstanceType>
	static void OnSubscribe(uint16_t connHandle, uint16_t attrHandle, uint8_t reason,
			bool prevNotify, bool curNotify, bool prevIndicate, bool curIndicate)
	{
		meta::ForTupleTypes<ServiceTuple>::Apply([&]<typename Svc>(Svc*) {
			return meta::ForTupleTypes<typename Svc::CharacteristicTuple>::Apply([&]<typename Chr>(Chr*) {
					if (attrHandle == Chr::valHandle) {
						Chr::template OnSubscribe<InstanceType>(connHandle, reason, prevNotify, curNotify, prevIndicate, curIndicate);
						return true;
					}
					return false;
				});
			});
	}
};


} // namespace opkey::ble
