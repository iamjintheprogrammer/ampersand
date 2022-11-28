#pragma once

#include <ampersand/meta/annotation.hpp>
#include <ampersand/meta/attribute.hpp>

namespace ampersand::meta {
    template <auto Method, typename AnnotationSet>
    struct method {
        static constexpr auto value = Method;
        using annotations           = AnnotationSet;
    };

    template <typename... Methods>
    using traits = boost::mp11::mp_list<Methods...>;
}