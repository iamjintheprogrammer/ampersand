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

    template <std::size_t Idx, typename... T>
    struct __search_if;

    template <std::size_t Idx, typename Predicate>
    struct __search_if<Idx, Predicate> {
        static constexpr std::size_t value = -1;
    };

    template <std::size_t Idx, typename Predicate, typename T>
    struct __search_if<Idx, Predicate, T> {
        template <typename _T>
        using __predicate = typename Predicate::predicate<_T>;
        static constexpr std::size_t value = (__predicate<T>::value)
                                           ? Idx
                                           : -1;
    };

    template <std::size_t Idx, typename Predicate, typename T, typename... Types>
    struct __search_if<Idx, Predicate, T, Types...> {
        template <typename _T>
        using __predicate = typename Predicate::predicate<_T>;
        static constexpr std::size_t value = (__predicate<T>::value)
                                           ? Idx
                                           : __search_if<Idx + 1, Predicate, Types...>::value;
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

    template <typename... T>
    struct search_if;

    template <typename Predicate, typename... Types>
    struct search_if<Predicate, type_table<Types...>> {
        static constexpr std::size_t npos  = -1;
        static constexpr std::size_t value = __search_if<0, Predicate, Types...>::value;
    };

    template <typename... T>
    inline constexpr std::size_t search_if_v = search_if<T...>::value;
}