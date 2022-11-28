#pragma once
#include <tuple>
#include <type_traits>

#include <ampersand/meta/annotation.hpp>
#include <ampersand/meta/attribute.hpp>
#include <ampersand/meta/method.hpp>

namespace ampersand::meta {
    template <typename... T>
    class object;

    template <typename... Attributes>
    class object<meta_type<Attributes...>> {
        using __attr   = std::tuple<typename Attributes::attribute_type...>;
              __attr   _M_Attr  ;
    public:
        using meta_type   = meta_type<Attributes...>;
    public:
        template <typename Attr> auto& operator[](Attr) { 
            return std::get
                <boost::mp11::mp_find
                    <meta_type, Attr>::value>(_M_Attr); 
        }
    };
}