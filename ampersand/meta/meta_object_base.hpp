#pragma once
#include <ampersand/meta/meta.hpp>

namespace ampersand::meta {
    template <typename BodyT, typename MetaType, typename... ActionT>
    class meta_object_base {
    protected:
        using body_type            = BodyT;
        using attribute_field_type = typename body_type::template attribute_field_type<MetaType>;

    protected:
        meta_object_base() {};
    protected:
        template <typename AttrT> 
        auto& _M_Get(AttrT) { 
            return body_type::get(_M_Base, AttrT{}, MetaType{}); 
        }
        
    protected:
        attribute_field_type _M_Base;
    };
}