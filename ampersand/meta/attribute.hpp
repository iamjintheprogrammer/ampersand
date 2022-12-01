#pragma once
#include <string_view>
#include <ampersand/meta/annotation.hpp>

namespace ampersand::meta {
    template <typename AttrT, typename... Annotation>
    struct attribute {
        using attribute_type = AttrT;
        using annotations    = boost::mp11::mp_list<Annotation...>;
    };

    template <typename AttrT>
    struct attribute<AttrT> {
        using attribute_type = AttrT;
        using annotations    = boost::mp11::mp_list<>;
    };
}