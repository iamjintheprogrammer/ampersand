#pragma once
#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

namespace ampersand::meta {
    template <concepts::attribute... Attributes>
    struct meta_type {
        using type = boost::mp11::mp_list<Attributes...>;
    };

    template <concepts::attribute... Attributes>
    meta_type(Attributes...)->meta_type<Attributes...>;

    template <typename... Attributes>
    constexpr auto make_meta_type(const Attributes&...) {
        return meta_type<Attributes...>{};
    }
}