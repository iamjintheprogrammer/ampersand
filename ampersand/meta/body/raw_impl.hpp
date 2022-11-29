#pragma once
#include <type_traits>
#include <ampersand/meta/meta.hpp>

namespace ampersand::meta::body {
    template <typename... T>
    struct __raw_size;

    template <typename AttrT, typename... AttrRemaining>
    struct __raw_size<meta_type<AttrT, AttrRemaining...>> {
        static constexpr std::size_t value
            = sizeof(typename AttrT::attribute_type)
                + __raw_size<meta_type<AttrRemaining...>>::value;
    };

    template <typename AttrT>
    struct __raw_size<meta_type<AttrT>> {
        static constexpr std::size_t value
            = sizeof(typename AttrT::attribute_type);
    };

    template <>
    struct __raw_size<> {
        static constexpr std::size_t value = 0;
    };

    template <typename... AttrT>
    inline constexpr std::size_t __raw_size_v = __raw_size<AttrT...>::value;

    template <typename... T>
    struct __raw_offset;

    template <typename T, typename AttrT, typename... AttrRemaining>
    struct __raw_offset<T, meta_type<AttrT, AttrRemaining...>> {
        static constexpr std::size_t value
            = (std::is_same_v<T, typename AttrT::attribute_type>)
                    ? 0
                    : __raw_offset<T, meta_type<AttrRemaining...>>::value;
    };

    template <typename T, typename AttrT>
    struct __raw_offset<T, meta_type<AttrT>> {
        static constexpr std::size_t value
            = (std::is_same_v<T, typename AttrT::attribute_type>)
                    ? 0
                    : sizeof(typename AttrT::attribute_type);
    };

    template <typename T>
    struct __raw_offset<T> {
        static constexpr std::size_t value = 0;
    };

    template <typename T, typename... AttrT>
    inline constexpr std::size_t __raw_offset_v = __raw_offset<T, AttrT...>::value;
}