#pragma once

#include <tuple>
#include <type_traits>


namespace opkey::ble::meta {


template<typename WantType, typename T>
using TypeOrVoid = std::conditional_t<std::is_same_v<WantType, T>, T, void>;

template<typename WantBaseType, typename T>
using DerivedTypeOrVoid = std::conditional_t<std::is_base_of_v<WantBaseType, T>, T, void>;


template<typename ElseType, typename... Ts>
struct _FirstNonVoid;

template<typename ElseType>
struct _FirstNonVoid<ElseType> {
	using Type = ElseType;
};

template<typename ElseType, typename T, typename... Ts>
struct _FirstNonVoid<ElseType, T, Ts...> {
    using Type = T;
};

template<typename ElseType, typename... Ts>
struct _FirstNonVoid<ElseType, void, Ts...> {
    using Type = typename _FirstNonVoid<ElseType, Ts...>::Type;
};

template<typename ElseType, typename... Ts>
using FirstNonVoid = typename _FirstNonVoid<ElseType, Ts...>::Type;


template<typename WantType, typename... Ts>
constexpr const bool HasType = (... || std::is_same_v<WantType, Ts>);

template<typename WantBaseType, typename... Ts>
constexpr const bool HasDerivedType = (... || std::is_base_of_v<WantBaseType, Ts>);


template<typename WantType, typename... Ts>
constexpr const bool CountType = (... + (std::is_same_v<WantType, Ts> ? 1 : 0));

template<typename WantBaseType, typename... Ts>
constexpr const uint8_t CountDerivedType = (... + (std::is_base_of_v<WantBaseType, Ts> ? 1 : 0));


template<typename WantType, typename ElseType, typename... Ts>
using GetType = FirstNonVoid<ElseType, TypeOrVoid<WantType, Ts>...>;

template<typename WantBaseType, typename ElseType, typename... Ts>
using GetDerivedType = FirstNonVoid<ElseType, DerivedTypeOrVoid<WantBaseType, Ts>...>;


template<typename WantedMixinType, class T>
struct _RecurseGetTypeByMixin {
	using Type = void;
};

template<typename WantedMixinType, class T, typename... Ts>
struct _GetTypeByMixin {
	using Type = void;
};


template<typename WantedMixinType, template<typename...> class T, typename... Ts>
struct _RecurseGetTypeByMixin<WantedMixinType, T<Ts...>> {
	using Type = typename _GetTypeByMixin<WantedMixinType, T<Ts...>, Ts...>::Type;
};

template<typename WantedMixinType, template<typename...> class T, typename... Ts>
struct _GetTypeByMixin<WantedMixinType, T<Ts...>, Ts...> {
	using Type = std::conditional_t
		< (... || std::is_same_v<WantedMixinType, Ts>)
		, T<Ts...>
		, FirstNonVoid<void, typename _RecurseGetTypeByMixin<WantedMixinType, Ts>::Type...>
		>;
};

template<typename WantedMixinType, class T>
struct _DispatchGetTypeByMixin {
	static_assert(not std::is_same_v<T, T>, "To use GetTypeByMixin, the given type must have a template parameter pack");
};

template<typename WantedMixinType, template<typename...> class T, typename... Ts>
struct _DispatchGetTypeByMixin<WantedMixinType, T<Ts...>> {
	using Type = typename _GetTypeByMixin<WantedMixinType, T<Ts...>, Ts...>::Type;
};

template<typename WantedMixinType, typename ElseType, class T>
using GetTypeByMixin = FirstNonVoid<ElseType, typename _DispatchGetTypeByMixin<WantedMixinType, T>::Type>;


template<typename Tuple, typename T>
struct _AppendTypeToTuple;

template<typename... Ts, typename T>
struct _AppendTypeToTuple<std::tuple<Ts...>, T> {
	using Type = std::tuple<Ts..., T>;
};

template<typename Tuple, typename T>
using AppendTypeToTuple = typename _AppendTypeToTuple<Tuple, T>::Type;


template<typename WantBaseType, typename Tuple, typename... Ts>
struct _ExtractDerivedTypes;

template<typename WantBaseType, typename Tuple>
struct _ExtractDerivedTypes<WantBaseType, Tuple> {
	using Type = Tuple;
};

template<typename WantBaseType, typename Tuple, typename T, typename... Ts>
struct _ExtractDerivedTypes<WantBaseType, Tuple, T, Ts...> {
    using Type = std::conditional_t
        < std::is_base_of_v<WantBaseType, T>
        , typename _ExtractDerivedTypes<WantBaseType, AppendTypeToTuple<Tuple, T>, Ts...>::Type
        , typename _ExtractDerivedTypes<WantBaseType, Tuple, Ts...>::Type
		>;
};

template<typename WantBaseType, typename... Ts>
using ExtractDerivedTypes = typename _ExtractDerivedTypes<WantBaseType, std::tuple<>, Ts...>::Type;


template<typename Tuple>
struct ForTupleTypes;

template<typename... Ts>
struct ForTupleTypes<std::tuple<Ts...>> {
	template<typename F>
	inline static void Apply(F&& f) {
		(... || f(static_cast<Ts*>(nullptr)));
	}
};


} // namespace opkey::ble::meta
