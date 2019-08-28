#pragma once

#include "ble_meta.h"
#include "ble_uuid.h"
#include "ble_service.h"


namespace opkey::ble {


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

	using ServiceTuple = ExtractDerivedTypes<ServiceTag, Options...>;
	static inline constexpr const size_t serviceCount = std::tuple_size_v<ServiceTuple>;

	static inline constexpr const std::array<ble_gatt_svc_def, serviceCount + 1> nimbleGattServiceDefinitions =
		{ (..., Service::NimbleServiceDefinition())
		, { 0, nullptr, nullptr, nullptr }
		};
};


} // namespace opkey::ble
