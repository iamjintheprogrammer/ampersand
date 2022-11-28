#pragma once
#include <ampersand/extension/javascript/class.hpp>

namespace ampersand::extension::javascript {
    template <typename... AnyType>
    class class_definition;

    template <typename... Attributes>
    class class_definition<meta::meta_type<Attributes...>> {
        using __tuple = std::tuple<typename Attributes::attribute_type...>;
              __tuple _M_Base;
    public:
        using meta_type = meta::meta_type<Attributes...>;
    public:
        
    };
}