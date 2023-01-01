#pragma once
#include <type_traits>

namespace ampersand::meta {
    template <typename... AnyType>
    class annotation;
    
    template <typename AnnotateType>
    class annotation<AnnotateType> {
        AnnotateType _M_Value;
    public:
        using      value_type =      AnnotateType;
        using       reference =       value_type&;
        using const_reference = const value_type&;
        using       pointer   =       value_type*;
        using const_pointer   = const value_type*;

        template <typename... InitArgs>
        constexpr annotation(InitArgs&&...);
        constexpr annotation(reference)    ;

        constexpr annotation(const annotation&)  = default;
        constexpr annotation      (annotation&&) = default;

    public:
        constexpr const_reference operator*();
    };

    template <typename AnnotateType>
    template <typename... InitArgs>
    constexpr annotation<AnnotateType>::annotation
        (InitArgs&&... pInitArgs)
            : _M_Value(pInitArgs...) {  }

    template <typename AnnotateType>
    constexpr annotation<AnnotateType>::annotation(reference pCopyValue)
        : _M_Value(pCopyValue) {}

    template <typename AnnotateType>
    constexpr annotation<AnnotateType>::const_reference
        annotation<AnnotateType>::operator*() {
            return _M_Value;
    }
}

namespace ampersand::meta::utility {
    template <typename... AnyType>   struct is_annotation                           : std::false_type {};
    template <typename AnnotateType> struct is_annotation<annotation<AnnotateType>> : std::true_type  {};
    template <typename... AnyType>   inline constexpr bool is_annotation_v = is_annotation<AnyType...>::value;
}

namespace ampersand::meta::concepts {
    template <typename... AnyType> concept annotation = utility::is_annotation_v<AnyType...>;
}