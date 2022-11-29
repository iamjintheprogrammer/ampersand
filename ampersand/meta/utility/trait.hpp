#pragma once
#include <type_traits>

#include <ampersand/meta/attribute.hpp>
#include <ampersand/meta/annotation.hpp>

namespace ampersand::meta::utility {
    template <typename... T>
    struct is_attribute                                        : std::false_type {};
    template <typename AttrT, typename... Annotation>
    struct is_attribute<meta::attribute<AttrT, Annotation...>> : std::true_type  {};
    template <typename AttrT>
    struct is_attribute<meta::attribute<AttrT>>                : std::true_type  {};

    template <typename T>
    inline constexpr bool is_attribute_v = is_attribute<T>::value;

    template <typename AnyAnnotation>
    struct is_annotation : std::is_base_of<annotation, AnyAnnotation> {};

    template <typename AnyAnnotation>
    inline constexpr bool is_annotation_v = is_annotation<AnyAnnotation>::value;
}