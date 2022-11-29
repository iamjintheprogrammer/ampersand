#pragma once
#include <ampersand/meta/meta.hpp>

#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

namespace ampersand::meta {
    template <typename... T>
    struct __raw_size;

    template <typename AttrT, typename... AttrRemaining>
    struct __raw_size<AttrT, AttrRemaining...> {
        static constexpr std::size_t value
            = sizeof(typename AttrT::attribute_type)
                + __raw_size<AttrRemaining...>::value;
    };

    template <typename AttrT>
    struct __raw_size<AttrT> {
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
    struct __raw_offset<T, AttrT, AttrRemaining...> {
        static constexpr std::size_t value
            = (std::is_same_v<T, typename AttrT::attribute_type>)
                    ? 0
                    : __raw_offset<T, AttrRemaining...>::value;
    };

    template <typename T, typename AttrT>
    struct __raw_offset<T, AttrT> {
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

    struct raw_body {
        template <concepts::attribute... AttrT>
        using attribute_field = std::uint8_t[__raw_size_v<AttrT...>];
        
        template <typename Target, typename... AttrT, std::size_t FieldSize>
        static auto& get(std::uint8_t(&pField)[FieldSize], meta_type<AttrT...>, Target) {
            return
                *reinterpret_cast<typename Target::attribute_type*>
                    (pField + __raw_offset_v<Target, AttrT...>);
        }
    };
}