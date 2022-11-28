#pragma once
#include <ampersand/meta/annotation.hpp>
#include <ampersand/meta/attribute.hpp>

namespace ampersand::meta {
    template <typename... Attributes>
    using meta_type      = boost::mp11::mp_list<Attributes...>;

    template <typename... Attributes>
    constexpr auto make_meta_type(const Attributes&...) {
        return meta_type<Attributes...>{};
    }
    
    template <typename MetaT, typename AttrT>
    using push_attribute = boost::mp11::mp_push_back<MetaT, AttrT>;

    template <typename MetaT, typename AttrT>
    using pop_attribute  = boost::mp11::mp_remove<MetaT, AttrT>;
}