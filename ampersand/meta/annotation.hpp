#pragma once
#include <type_traits>
#include <boost/mp11.hpp>

namespace ampersand::meta {
    struct annotation {};
    
    template <typename AnyAnnotation>
    struct is_annotation { static constexpr bool value = std::is_base_of_v<annotation, AnyAnnotation>; };

    template <typename AnyAnnotation>
    inline constexpr bool is_annotation_v = is_annotation<AnyAnnotation>::value;

    template <typename... AnyAnnotation>
    using annotation_set = boost::mp11::mp_list<AnyAnnotation...>;

    template <typename Annotation, typename AnnotationSet>
    using push_annotation = boost::mp11::mp_push_back<AnnotationSet, Annotation>;

    template <typename Annotation, typename AnnotationSet>
    using pop_annotation  = boost::mp11::mp_remove<AnnotationSet, Annotation>;

    template <typename Annotation, typename AnnotationSet>
    inline constexpr bool have_annotation
        = boost::mp11::mp_find<AnnotationSet, Annotation>::value
                != boost::mp11::mp_size<AnnotationSet>::value;

    template <typename Predicate, typename AnnotationSet>
    inline constexpr bool have_specific_annotation
        = boost::mp11::mp_find_if<AnnotationSet, Predicate>::value
                != boost::mp11::mp_size<AnnotationSet>::value;
}