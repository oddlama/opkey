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
struct AdvertiseUuid : private ServerMixinTag { };

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
	static_assert(connectHandlerCount <= 1, "Multiple connect handlers are not supported");
	static_assert(disconnectHandlerCount <= 1, "Multiple disconnect handlers are not supported");

	static inline constexpr const bool hasConnectHandler = connectHandlerCount > 0;
	static inline constexpr const bool hasDisconnectHandler = disconnectHandlerCount > 0;
	using ConnectHandler = meta::GetDerivedType<server_options::ConnectHandlerTag, struct NoConnectHandler, Options...>;
	using DisconnectHandler = meta::GetDerivedType<server_options::DisconnectHandlerTag, struct NoDisconnectHandler, Options...>;

	using ServiceTuple = meta::ExtractDerivedTypes<ServiceTag, Options...>;
	static inline constexpr const auto nimbleGattServiceDefinitions =
		ExpandServiceDefinitions<ServiceTuple>::value;

	// TODO get all uuids from services with AdvertiseUuid tag
	// + all AdvertiseUuid<Uuid16> from here
	//
	// TODO same for 128

	static void OnConnect(const ble_gap_conn_desc& desc) {
		if constexpr (hasConnectHandler) {
			ConnectHandler::OnConnect(desc);
		}
	}

	static void OnDisconnect(int reason, const ble_gap_conn_desc& desc) {
		if constexpr (hasDisconnectHandler) {
			DisconnectHandler::OnDisconnect(reason, desc);
		}
	}

	static void OnSubscribe(uint16_t connHandle, uint16_t attrHandle, uint8_t reason,
			bool prevNotify, bool curNotify, bool prevIndicate, bool curIndicate)
	{ }
};


} // namespace opkey::ble
