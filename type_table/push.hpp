#pragma once
#include <cstdint>
#include <cstddef>

#include <type_table/type_table.hpp>

namespace ampersand::type_table {
    template <typename... T>
    struct push_front;

    template <typename... T>
    struct push_front;

    template <typename T, typename... ListType>
    struct push_front<T, type_table<ListType...>> {
        using type = type_table<T, ListType...>;
    };

    template <typename... T>
    using push_front_t = typename push_front<T...>::type;

    template <typename... T>
    struct push_back;

    template <typename T, typename... ListType>
    struct push_back<T, type_table<ListType...>> {
        using type = type_table<ListType..., T>;
    };

    template <typename... T>
    using push_back_t = typename push_back<T...>::type;

    template <std::size_t Index, typename... T>
    struct __push_at;

    template <std::size_t Index    ,
              typename T           ,
              typename... ListType ,
              typename    Remain   ,
              typename... Remaining>
    struct __push_at<Index, T, type_table<ListType...>,  Remain, Remaining...> {
        using type = typename __push_at<Index - 1, T, type_table<ListType..., Remain>, Remaining...>::type;
    };

    template <std::size_t Index   ,
              typename T          ,
              typename... ListType,
              typename    Remain>
    struct __push_at<Index, T, type_table<ListType...>, Remain> {
        using type = type_table<ListType..., Remain, T>;
    };

    template <typename T, typename... ListType, typename... Remaining>
    struct __push_at<0, T, type_table<ListType...>, Remaining...> {
        using type = type_table<ListType..., T, Remaining...>;
    };

    template <typename T, typename... ListType, typename Remaining>
    struct __push_at<0, T, type_table<ListType...>, Remaining> {
        using type = type_table<ListType..., T, Remaining>;
    };

    template <std::size_t Index, typename... T>
    struct push_at;

    template <std::size_t Index, typename T, typename... Remaining>
    struct push_at<Index, T, type_table<Remaining...>> {
        using type = typename __push_at<Index, T, type_table<>, Remaining...>::type;
    };
}