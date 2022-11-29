#pragma once

#include <ampersand/meta/annotation.hpp>
#include <ampersand/meta/attribute.hpp>

namespace ampersand::meta {
    template <auto Method, typename... Annotations>
    struct method {
        static constexpr auto value = Method;
        using annotations           = boost::mp11::mp_list<Annotations...>;
    };

    template <typename... Methods>
    struct trait {
        using type = boost::mp11::mp_list<Methods...>;
    };
}