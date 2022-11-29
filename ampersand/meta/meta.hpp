#pragma once
#include <ampersand/meta/annotation.hpp>
#include <ampersand/meta/attribute.hpp>

#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

namespace ampersand::meta {
    template <typename... Attributes>
    struct meta_type {
        using type = boost::mp11::mp_list<Attributes...>;
    };

    template <typename... Attributes>
    constexpr auto make_meta_type(const Attributes&...) {
        return meta_type<Attributes...>{};
    }
}