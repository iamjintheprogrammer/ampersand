#pragma once
#include <ampersand/meta/meta_object_base.hpp>

namespace ampersand::meta {
    template <typename... AnyT>
    class meta_object;

    template <typename BodyT, typename... AttributeT>
    class meta_object     <BodyT, meta_type<AttributeT...>>
        : meta_object_base<BodyT, meta_type<AttributeT...>> {
        using base_type = meta_object_base<BodyT, meta_type<AttributeT...>>;
    public:
        using meta_type            =          meta_type<AttributeT...>       ;
        using body_type            = typename base_type::body_type           ;
        using attribute_field_type = typename base_type::attribute_field_type;

    public:
        meta_object(BodyT, meta_type) : base_type() {}
        meta_object()                 : base_type() {}

    public:
        attribute_field_type& attribute_field() { 
            return this->_M_Base;
        }
        
        template <typename Attribute>
        auto& operator[](Attribute) { return this->_M_Get(Attribute{}); }
    };

    template <typename BodyT, typename MetaType>
    meta_object(BodyT, MetaType)->meta_object<BodyT, MetaType>;
}