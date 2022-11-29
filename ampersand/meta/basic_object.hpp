#pragma once
#include <ampersand/meta/object_base.hpp>

namespace ampersand::meta {

    template <typename BodyT, typename MetaType>
    class basic_object : object_base <BodyT, MetaType> {
        using _Base = object_base<BodyT, MetaType>;
    public:
        using        body_type = typename _Base       ::body_type;
        using meta_object_type = typename _Base::meta_object_type;
        using       field_type = typename _Base      ::field_type;

    public:
        basic_object() : _Base() {}

    public:
        template <typename Attr> 
        auto& operator[](Attr) { return this->_M_Get(Attr{}); }
    };
}