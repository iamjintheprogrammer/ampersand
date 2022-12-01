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
        template <typename AttrT> auto&      _M_Get      (AttrT);
        template <typename AttrT> index_type _M_Get_Index(AttrT);
        
    protected:
        attribute_field_type _M_Base;
    };

    template <typename MetaType>
    class meta_object_base<body::tag, MetaType> {
    protected:
        using body_type            = body::tag;
        using attribute_field_type = typename body_type::template attribute_field_type<MetaType>;
        
        using index_type           = std::ptrdiff_t;
        using name_type            = std::string;

    protected:
        meta_object_base() {};
    public:
        template <typename AttrT> auto&      _M_Get      (AttrT);
        template <typename AttrT> index_type _M_Get_Index(AttrT);
        template <typename AttrT> name_type& _M_Get_Name (AttrT);
        
    protected:
        attribute_field_type _M_Base;
    };

    template <typename BodyT, typename MetaType>
    template <typename AttrT>
    auto&
        meta_object_base<BodyT, MetaType>::_M_Get
            (AttrT pAttribute) {
        return body_type::get(_M_Base, AttrT{}, MetaType{});
    }

    template <typename BodyT, typename MetaType>
    template <typename AttrT>
    typename
        meta_object_base<BodyT, MetaType>::index_type
            meta_object_base<BodyT, MetaType>::_M_Get_Index
                (AttrT pAttribute) {
        return body_type::get_index(_M_Base, AttrT{}, MetaType{});
    }

    template <typename MetaType>
    template <typename AttrT>
    auto&
        meta_object_base<body::tag, MetaType>::_M_Get
            (AttrT pAttribute) {
        return body_type::get(_M_Base, AttrT{}, MetaType{});
    }

    template <typename MetaType>
    template <typename AttrT>
    typename
        meta_object_base<body::tag, MetaType>::index_type
            meta_object_base<body::tag, MetaType>::_M_Get_Index
                (AttrT pAttribute) {
        return body_type::get_index(_M_Base, AttrT{}, MetaType{});
    }

    template <typename MetaType>
    template <typename AttrT>
    typename
        meta_object_base<body::tag, MetaType>::name_type&
            meta_object_base<body::tag, MetaType>::_M_Get_Name
                (AttrT pAttribute) {
        return body_type::get_name(_M_Base, AttrT{}, MetaType{});
    }
}