#pragma once
#include <ampersand/meta/utility/trait.hpp>

namespace ampersand::meta::concepts {
    template <typename AttrT>   concept attribute  = utility::is_attribute_v <AttrT>  ;
    template <typename AnnotT>  concept annotation = utility::is_annotation_v<AnnotT> ;
    template <typename MethodT> concept method     = utility::is_method_v    <MethodT>;
}