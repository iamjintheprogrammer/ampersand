#pragma once
#include <string_view>

#include <ampersand/meta/annotation.hpp>
#include <ampersand/meta/condition.hpp>

namespace ampersand::meta {
    template <typename AttrT, typename... Annotation>
    struct attribute {
        using value_type = AttrT;

        template <typename RAttr, typename... RAnnot> auto operator<  (attribute<RAttr, RAnnot...>&);
        template <typename RAttr, typename... RAnnot> auto operator<= (attribute<RAttr, RAnnot...>&);
        template <typename RAttr, typename... RAnnot> auto operator>  (attribute<RAttr, RAnnot...>&);
        template <typename RAttr, typename... RAnnot> auto operator>= (attribute<RAttr, RAnnot...>&);

        template <typename RAttr, typename... RAnnot> auto operator== (attribute<RAttr, RAnnot...>&);
        template <typename RAttr, typename... RAnnot> auto operator!= (attribute<RAttr, RAnnot...>&);

        template <typename AddAnnotation>             auto operator | (AddAnnotation);
    };

    template <typename AttrT, typename... Annotation>
    template <typename RAttr, typename... RAnnot>
    auto
        attribute<AttrT, Annotation...>::operator<
            (attribute<RAttr, RAnnot...>& pRhs) {
        return
            binary_condition(less_than{}, *this, pRhs);
    }

    template <typename AttrT, typename... Annotation>
    template <typename RAttr, typename... RAnnot>
    auto
        attribute<AttrT, Annotation...>::operator<=
            (attribute<RAttr, RAnnot...>& pRhs) {
        return
            binary_condition(less_or_equal{}, *this, pRhs);
    }

    template <typename AttrT, typename... Annotation>
    template <typename RAttr, typename... RAnnot>
    auto
        attribute<AttrT, Annotation...>::operator>
            (attribute<RAttr, RAnnot...>& pRhs) {
        return
            binary_condition(greater_than{}, *this, pRhs);
    }

    template <typename AttrT, typename... Annotation>
    template <typename RAttr, typename... RAnnot>
    auto
        attribute<AttrT, Annotation...>::operator>=
            (attribute<RAttr, RAnnot...>& pRhs) {
        return
            binary_condition(greater_or_equal{}, *this, pRhs);
    }

    template <typename AttrT, typename... Annotation>
    template <typename RAttr, typename... RAnnot>
    auto
        attribute<AttrT, Annotation...>::operator==
            (attribute<RAttr, RAnnot...>& pRhs) {
        return
            binary_condition(equal_with{}, *this, pRhs);
    }

    template <typename AttrT, typename... Annotation>
    template <typename RAttr, typename... RAnnot>
    auto
        attribute<AttrT, Annotation...>::operator!=
            (attribute<RAttr, RAnnot...>& pRhs) {
        return
            binary_condition(different_with{}, *this, pRhs);
    }

    template <typename AttrT, typename... Annotation>
    template <typename AddAnnotation>
    auto
        attribute<AttrT, Annotation...>::operator|
            (AddAnnotation) {
        if constexpr
            (std::is_base_of_v<annotation, AddAnnotation>)
                return
                    attribute<AttrT, Annotation..., AddAnnotation> {};
        else
            *this;
    }
}