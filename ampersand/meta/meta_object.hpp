#pragma once
#include <ampersand/meta/meta_object_base.hpp>
#include <ampersand/meta/meta_object_impl.hpp>

namespace ampersand::meta {
    template <typename... AnyT>
    class meta_object;

    template <typename BodyT, typename... AttributeT>
    class meta_object            <BodyT, meta_type<AttributeT...>>
        : public meta_object_base<BodyT, meta_type<AttributeT...>> {
        using base_type = meta_object_base<BodyT, meta_type<AttributeT...>>;
    public:
        using attribute_field_type = typename base_type::attribute_field_type;

    public:
        meta_object(BodyT, meta_type<AttributeT...>) : base_type() {} // For CTAD Support
        meta_object()                                : base_type() {}

    public:
        attribute_field_type& attribute_field() {
            return this->_M_Base;
        }
    public:
        template <typename RBodyT, typename... RAttributeT>
        auto& 
            operator=
                (meta_object<RBodyT, meta::meta_type<RAttributeT...>>& pRhs) {
            __adapt_object(*this, pRhs);
            return *this;
        }
        
        template <typename Attribute>
        typename Attribute::value_type& 
            operator[](Attribute) { 
                return this->_M_Get(Attribute{}); 
        }
    };

    template <typename KeyType, typename... AttributeT>
    class meta_object                     <body::tag<KeyType>, meta_type<AttributeT...>>
        : public meta_object_base         <body::tag<KeyType>, meta_type<AttributeT...>> {
        using base_type = meta_object_base<body::tag<KeyType>, meta_type<AttributeT...>>;
    public:
        using attribute_field_type = typename base_type::attribute_field_type;

        using index_type = typename base_type::index_type;
        using key_type   = typename base_type::key_type  ;

    public:
        meta_object(body::tag<KeyType>, meta_type<AttributeT...>) : base_type() {} // For CTAD Support
        meta_object()                                             : base_type() {}

    public:
        attribute_field_type& attribute_field() {
            return this->_M_Base;
        }
    public:
        template <typename RBodyT, typename... RAttributeT>
        auto& operator=(meta_object<RBodyT, meta::meta_type<RAttributeT...>>& pRhs) {
            __adapt_object(*this, pRhs);
            return *this;
        }
        
        template <typename Attribute>
        auto&      operator[](Attribute)     { return this->_M_Get       (Attribute{}); }
        auto&      operator[](key_type pKey) { return this->_M_Get_By_Key(pKey)       ; }
        template <typename Attribute>
        key_type&  key_of    (Attribute)     { return this->_M_Get_Key(Attribute{}); }
    };

    template <typename BodyT, typename MetaType>
    meta_object(BodyT, MetaType)->meta_object<BodyT, MetaType>;
}