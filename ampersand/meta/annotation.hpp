#pragma once
#include <type_traits>
#include <ampersand/meta/details/annotation.hpp>

namespace ampersand::meta {
    template <typename... AnyType>
    class annotation;
    
    template <typename AnnotateType>
    class annotation<AnnotateType> {
        AnnotateType _M_Value;
    public:
        using value_type       = AnnotateType;
        constexpr annotation() = default;
    };

    inline constexpr annotation   <__public_attr>    public_attribute;
    inline constexpr annotation  <__private_attr>   private_attribute;
    inline constexpr annotation<__protected_attr> protected_attribute;
    
    inline constexpr annotation <__dynamic_attr>    dynamic_attribute;
    inline constexpr annotation  <__static_attr>     static_attribute;
    inline constexpr annotation<__constant_attr>   constant_attribute;
}

namespace ampersand::meta::utility {
    template <typename... AnyType>   struct is_annotation                           : std::false_type {};
    template <typename AnnotateType> struct is_annotation<annotation<AnnotateType>> : std::true_type  {};
    template <typename... AnyType>   inline constexpr bool is_annotation_v = is_annotation<AnyType...>::value;
}

namespace ampersand::meta::concepts {
    template <typename... AnyType> concept annotation = utility::is_annotation_v<AnyType...>;
}