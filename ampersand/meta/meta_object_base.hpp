#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/body/tag.hpp>

namespace ampersand::meta {
    template <typename BodyT, typename MetaType>
    class meta_object_base {
    protected:
        using body_type            = BodyT;
        using attribute_field_type = typename body_type::template attribute_field_type<MetaType>;
        using index_type           = std::ptrdiff_t;

    protected:
        meta_object_base() {};
    public:
        template <typename AttrT> typename AttrT::value_type& _M_Get      (AttrT);
        template <typename AttrT> index_type                  _M_Get_Index(AttrT);
      
    protected:
        attribute_field_type _M_Base;
    };

    template <typename KeyType, typename MetaType>
    class meta_object_base<body::tag<KeyType>, MetaType> {
    protected:
        using body_type            = body::tag<KeyType>;
        using attribute_field_type = typename body_type::template attribute_field_type<MetaType>;
        
        using index_type           = std::ptrdiff_t;
        using key_type             = KeyType;

    protected:
        meta_object_base() {};
    public:
        template <typename AttrT> typename AttrT::value_type& _M_Get       (AttrT);
        template <typename AttrT> index_type                  _M_Get_Index (AttrT);
        template <typename AttrT> key_type&                   _M_Get_Key   (AttrT);

    protected:
        attribute_field_type _M_Base;
    };

    template <typename BodyT, typename MetaType>
    template <typename AttrT>
    typename AttrT::value_type&
        meta_object_base<BodyT, MetaType>::_M_Get
            (AttrT pAttribute) {
        return body_type::get<MetaType>(_M_Base, pAttribute);
    }

    template <typename BodyT, typename MetaType>
    template <typename AttrT>
    typename
        meta_object_base<BodyT, MetaType>::index_type
            meta_object_base<BodyT, MetaType>::_M_Get_Index
                (AttrT pAttribute) {
        return body_type::get_index<MetaType>(_M_Base, pAttribute);
    }

    template <typename KeyType, typename MetaType>
    template <typename AttrT>
    typename AttrT::value_type&
        meta_object_base<body::tag<KeyType>, MetaType>::_M_Get
            (AttrT pAttribute) {
        return body_type::get<MetaType>(_M_Base, AttrT{});
    }

    template <typename KeyType, typename MetaType>
    template <typename AttrT>
    typename
        meta_object_base<body::tag<KeyType>, MetaType>::index_type
            meta_object_base<body::tag<KeyType>, MetaType>::_M_Get_Index
                (AttrT pAttribute) {
        return body_type::get_index<MetaType>(_M_Base, pAttribute);
    }

    template <typename KeyType, typename MetaType>
    template <typename AttrT>
    typename
        meta_object_base<body::tag<KeyType>, MetaType>::key_type&
            meta_object_base<body::tag<KeyType>, MetaType>::_M_Get_Key
                (AttrT pAttribute) {
        return body_type::get_key<MetaType>(_M_Base, pAttribute);
    }
}