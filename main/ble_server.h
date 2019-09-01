#pragma once

#include "ble_meta.h"
#include "ble_uuid.h"
#include "ble_service.h"


namespace opkey::ble {


struct ServerMixinTag { };

namespace server_options {

struct ConnectCallbackTag : private ServerMixinTag { };
struct DisconnectCallbackTag : private ServerMixinTag { };

template<typename F>
struct ConnectCallback : private ConnectCallbackTag { };

template<typename F>
struct DisconnectCallback : private DisconnectCallbackTag { };

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

	using ServiceTuple = meta::ExtractDerivedTypes<ServiceTag, Options...>;
	static inline constexpr const size_t serviceCount = std::tuple_size_v<ServiceTuple>;
	static inline constexpr const std::array<ble_gatt_svc_def, serviceCount + 1> nimbleGattServiceDefinitions =
		ExpandServiceDefinitions<ServiceTuple>::value;
};


} // namespace opkey::ble
