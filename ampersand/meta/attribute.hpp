#pragma once
#include <ampersand/meta/annotation.hpp>

namespace ampersand::meta {
    template <typename... AnyType>
    struct attribute;

    template <typename AttrT, typename... AnyAnnotation>
    struct attribute<AttrT, annotation_set<AnyAnnotation...>> {
        using attribute_type = AttrT;
        using annotations    = annotation_set<AnyAnnotation...>;
    };
}