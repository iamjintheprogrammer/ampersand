#pragma once
#include <type_traits>
#include <type_table/type_table.hpp>

namespace ampersand::type_table {
    template <typename... T>
    struct __contains_of;

    template <typename T, typename U, typename... Types>
    struct __contains_of<T, U, Types...> {
        static constexpr bool __value = (std::is_same_v<T, U>)
                                      ? true
                                      : __contains_of<T, Types...>::__value;
    };

    template <typename T, typename U>
    struct __contains_of<T, U> {
        static constexpr bool __value = std::is_same_v<T, U>;
    };

    template <typename T>
    struct __contains_of<T> {
        static constexpr bool __value = false;
    };

    template <typename... T>
    struct contains_of;

    template <typename T, typename... Types>
    struct contains_of<T, type_table<Types...>> {
        static constexpr bool value = __contains_of<T, Types...>::__value;
    };

    template <typename... Types>
    inline constexpr bool contains_of_v = contains_of<Types...>::value;
}