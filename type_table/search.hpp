#pragma once
#include <type_traits>
#include <type_table/type_table.hpp>

namespace ampersand::type_table {
    template <std::size_t Idx, typename... T>
    struct __search;

    template <std::size_t Idx, typename T>
    struct __search<Idx, T> {
        static constexpr std::size_t value = -1;
    };

    template <std::size_t Idx, typename T, typename U>
    struct __search<Idx, T, U> {
        static constexpr std::size_t value = (std::is_same_v<T, U>)
                                           ? Idx
                                           : -1;
    };

    template <std::size_t Idx, typename T, typename U, typename... Types>
    struct __search<Idx, T, U, Types...> {
        static constexpr std::size_t value = (std::is_same_v<T, U>)
                                           ? Idx
                                           : __search<Idx + 1, T, Types...>::value;
    };

    template <typename... T>
    struct search;

    template <typename T, typename... Types>
    struct search<T, type_table<Types...>> {
        static constexpr std::size_t npos  = -1;
        static constexpr std::size_t value = __search<0, T, Types...>::value;
    };

    template <typename... T>
    inline constexpr std::size_t search_v = search<T...>::value;
}