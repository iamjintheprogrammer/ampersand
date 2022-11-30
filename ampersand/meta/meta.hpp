#pragma once
#include <boost/mp11.hpp>

namespace ampersand::meta {
    template <typename... Attributes>
    struct meta_type {
        using type = boost::mp11::mp_list<Attributes...>;
        constexpr meta_type(Attributes...) {}
        constexpr meta_type()              {}
    };

    template <typename... AttributeT>
    meta_type(AttributeT...)->meta_type<AttributeT...>;
}