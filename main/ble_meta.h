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


} // namespace opkey::ble::meta
