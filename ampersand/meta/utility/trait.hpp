#pragma once
#include <type_traits>

#include <ampersand/meta/attribute.hpp>
#include <ampersand/meta/annotation.hpp>

#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <ampersand/meta/condition.hpp>

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

    template <typename AnyType>       struct is_meta_type                           : std::false_type {};
    template <typename... Attributes> struct is_meta_type<meta_type<Attributes...>> : std::true_type  {};
    template <typename T>             
    inline constexpr bool  is_meta_type_v = is_meta_type<T>::value;

    template <typename AnyType>                  
    struct is_meta_object                                          : std::false_type {};
    template <typename BodyT, typename... AttrT> 
    struct is_meta_object<meta_object<BodyT, meta_type<AttrT...>>> : std::true_type  {};

    template <typename AnyType>
    inline constexpr bool is_meta_object_v = is_meta_object<AnyType>::value;

    template <typename...AnyType>
	struct is_binary_condition                                         : std::false_type {};
	template <typename Verb, typename LField, typename RField>
	struct is_binary_condition<binary_condition<Verb, LField, RField>> : std::true_type  {};
	template <typename... AnyType>
	inline constexpr bool is_binary_condition_v = is_binary_condition<AnyType...>::value;
}