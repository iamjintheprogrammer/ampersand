#pragma once
#include <meta/field.hpp>
#include <meta/field_utility.hpp>

#include <meta/attribute.hpp>
#include <meta/meta_type.hpp>

namespace ampersand::describe {
    template <std::ptrdiff_t Off, typename... T>
    struct __raw_offset;

    template <std::ptrdiff_t Off, typename T, typename Type, typename... Remaining>
    struct __raw_offset<Off, T, Type, Remaining...> {
        static constexpr std::ptrdiff_t value
            = (std::is_same_v<T, Type>)
            ? Off
            : __raw_offset<Off + sizeof(Type), T, Remaining...>::value;
    };

    template <std::ptrdiff_t Off, typename T, typename Type>
    struct __raw_offset<Off, T, Type> {
        static constexpr std::ptrdiff_t value
            = (std::is_same_v<T, Type>)
                ?  Off
                :  -1;
    };

    template <typename... T>
    struct __raw_field_size;

    template <typename T, typename... Types>
    struct __raw_field_size<T, Types...> {
        static constexpr std::size_t value = sizeof(T) + __raw_field_size<Types...>::value;
    };

    template <typename T>
    struct __raw_field_size<T> {
        static constexpr std::size_t value = sizeof(T);
    };

    template <>
    struct __raw_field_size<> {
        static constexpr std::size_t value = 0;
    };

    template <typename... T>
    class raw_field;

    template <typename... Attr, typename... FieldT>
    class raw_field
            <meta::meta_type
            <meta::attribute_set<Attr...>, FieldT...>> {
        std::uint8_t _M_Base[__raw_field_size<typename FieldT::value_type...>::value];
    public:
        using size_type       = std::size_type;
        using difference_type = std::ptrdiff_t;

        using value_type      = std::uint8_t;
        using reference       = value_type& ;
        using pointer         = value_type* ;

    public:
        reference operator[](difference_type pDiff) { return _M_Base[pDiff]; }
    };

    
}