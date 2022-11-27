#pragma once
#include <type_traits>

namespace ampersand::utility {
    template <std::size_t Idx, typename... T>
    struct __index_of;

    template <std::size_t Idx, typename T>
    struct __index_of<Idx, T> {
        static constexpr std::size_t value = -1;
    };

    template <std::size_t Idx, typename T, typename U>
    struct __index_of<Idx, T, U> {
        static constexpr std::size_t value = (std::is_same_v<T, U>)
                                           ? Idx
                                           : -1;
    };

    template <std::size_t Idx, typename T, typename U, typename... Types>
    struct __index_of<Idx, T, U, Types...> {
        static constexpr std::size_t value = (std::is_same_v<T, U>)
                                           ? Idx
                                           : __index_of<Idx + 1, T, Types...>::value;
    };

    template <typename T, typename... Types>
    struct index_of {
        static constexpr std::size_t value = __index_of<0, T, Types...>::value;
    };
}