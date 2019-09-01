#pragma once

#include "ble_meta.h"
#include "ble_uuid.h"
#include "ble_characteristic.h"


namespace opkey::ble {


template<typename Tuple>
struct ExpandCharacteristicDefinitions;

template<typename... Ts>
struct ExpandCharacteristicDefinitions<std::tuple<Ts...>> {
	static inline constexpr const std::array<ble_gatt_chr_def, sizeof...(Ts) + 1> value =
		{ Ts::NimbleCharacteristicDefinition()...
		, { nullptr, nullptr, nullptr, nullptr, 0, 0, nullptr }
		};
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
	using CharacteristicTuple = meta::ExtractDerivedTypes<CharacteristicTag, Options...>;
	static inline constexpr const size_t characteristicCount = std::tuple_size_v<CharacteristicTuple>;
	static inline constexpr const std::array<ble_gatt_svc_def, characteristicCount + 1> nimbleGattCharacteristicDefinitions =
		ExpandCharacteristicDefinitions<CharacteristicTuple>::value;

	constexpr static ble_gatt_svc_def NimbleServiceDefinition() noexcept {
		return
			{ // .type
				BLE_GATT_SVC_TYPE_PRIMARY
			, // .uuid
				&UuidType::nimbleUuid
			, // .includes
				nullptr
			, // .characteristics
				nimbleGattCharacteristicDefinitions.data()
			};
	}
};


} // namespace opkey::ble
