#pragma once

#include <type_traits>


namespace opkey::ble {


namespace detail {


template<typename WantType, typename T>
using GetType = std::conditional_t<std::is_same_v<WantType, T>, T, void>;

template<typename WantBaseType, typename T>
using GetDerivedType = std::conditional_t<std::is_base_of_v<WantBaseType, T>, T, void>;


template<typename ElseType, typename... Ts>
struct _FirstNonVoid;

template<typename ElseType>
struct _FirstNonVoid<ElseType> {
	using Type = ElseType;
};

template<typename ElseType, typename T, typename... Ts>
struct _FirstNonVoid<ElseType, T, Ts...> {
    using Type = std::conditional_t
        < std::is_same_v<T, void>
        , typename _FirstNonVoid<ElseType, Ts...>::Type
        , T>;
};


template<typename WantType, typename... Ts>
constexpr const bool HasType = (... || std::is_same_v<WantType, Ts>);

template<typename WantBaseType, typename... Ts>
constexpr const bool HasDerivedType = (... || std::is_base_of_v<WantBaseType, Ts>);


template<typename ElseType, typename... Ts>
using FirstNonVoid = typename _FirstNonVoid<ElseType, Ts...>::Type;

template<typename WantBaseType, typename ElseType, typename... Ts>
using GetType = FirstNonVoid<ElseType, GetType<WantType, Ts>...>;

template<typename WantBaseType, typename ElseType, typename... Ts>
using GetDerivedType = FirstNonVoid<ElseType, GetDerived<WantBaseType, Ts>...>;


} // namespace detail


static void Init(const char* name);


} // namespace opkey::ble
