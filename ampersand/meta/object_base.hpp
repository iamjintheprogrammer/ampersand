#pragma once

#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

namespace ampersand::meta {
    template <typename... AnyType>
    class object_base;

    template <typename BodyT, typename... Attributes>
    class object_base <BodyT, meta_type<Attributes...>> {
    protected:
        using        body_type = BodyT;
        using meta_object_type = meta_type                 <Attributes...>;
        using       field_type = body_type::attribute_field<Attributes...>;

    protected:
        template <typename InAttr>
        auto _M_Get (InAttr) {
            return body_type::get(_M_Base, meta_object_type{}, InAttr{});
        }

    private:
        field_type _M_Base;
    };
}