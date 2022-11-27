#pragma once

#include <cstdint>
#include <cstddef>

#include <type_table/type_table.hpp>

namespace ampersand::type_table {
    template <typename... T>
    struct pop_front;

    template <typename T, typename... ListType>
    struct pop_front<type_table<T, ListType...>> {
        using type = type_table<ListType...>;
    };

    template <typename T>
    struct pop_front<type_table<T>> { using type = type_table<>; };

    template <>
    struct pop_front<type_table<>>  { using type = type_table<>; };

    template <typename T>
    using  pop_front_t = typename pop_front<T>::type;

    template <typename... T>
    struct __pop_back;

    template <typename... ListType, typename T>
    struct __pop_back<type_table<ListType...>, T> {
        using __type = type_table<ListType...>;
    };

    template <typename... ListType, typename T, typename... Remaining>
    struct __pop_back<type_table<ListType...>, T, Remaining...> {
        using __type = typename __pop_back<type_table<ListType..., T>, Remaining...>::__type;
    };

    template <typename... T>
    struct pop_back;

    template <typename... ListType>
    struct pop_back<type_table<ListType...>> {
        using type = typename __pop_back<type_table<>, ListType...>::__type;
    };

    template <typename T>
    struct pop_back<type_table<T>> { using type = type_table<>; };

    template <>
    struct pop_back<type_table<>> { using type = type_table<>; };

    template <typename T>
    using pop_back_t = typename pop_back<T>::type;

    template <std::size_t Index, typename... T>
    struct __pop_at;

    template <std::size_t Index    ,
              typename... TableType,
              typename            T,
              typename... Remaining>
    struct __pop_at<Index, type_table<TableType...>, T, Remaining...> {
        using type = typename __pop_at<Index - 1, type_table<TableType..., T>, Remaining...>::type;
    };

    template <typename... TableType,
              typename    T,
              typename... Remaining>
    struct __pop_at<0, type_table<TableType...>, T, Remaining...> {
        using type = type_table<TableType..., Remaining...>;
    };

    template <typename... TableType,
              typename    T>
    struct __pop_at<0, type_table<TableType...>, T> {
        using type = type_table<TableType...>;
    };

    template <std::size_t Index,
              typename... TableType,
              typename    T>
    struct __pop_at<Index, type_table<TableType...>, T> {
        using type = type_table<TableType...>;
    };

    template <std::size_t Index, typename... TableType>
    struct pop_at;

    template <std::size_t Index, typename... TableType>
    struct pop_at<Index, type_table<TableType...>> {
        using type = typename __pop_at<Index, type_table<>, TableType...>::type;
    };
}