#pragma once
#include <ampersand/meta/utility/trait.hpp>

namespace ampersand::meta::concepts {
    template <typename AttrT>   concept attribute  = utility::template is_attribute_v <AttrT>  ;
    template <typename AnnotT>  concept annotation = utility::template is_annotation_v<AnnotT> ;
}