#pragma once
#include <ampersand/meta/meta.hpp>

namespace ampersand::meta {
    template <typename BodyT, typename MetaType>
    class meta_object {
    public:
        using body_type            = BodyT;
        using attribute_field_type = typename body_type::attribute_field_type<MetaType>;

    public:
        meta_object() = default;
    };
}