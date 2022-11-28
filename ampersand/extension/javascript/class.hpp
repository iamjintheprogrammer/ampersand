#pragma once
#include <ampersand/meta/meta.hpp>

namespace ampersand::extension::javascript {
namespace annotation {
    struct field        : meta::annotation {};
    template <auto Method>
    struct method       : meta::annotation { static constexpr auto value = Method; };

    struct dynamic_attr : meta::annotation {};
    struct static_attr  : meta::annotation {};

    struct private_attr : meta::annotation {};
    struct public_attr  : meta::annotation {};
}

namespace attribute {
    template <typename FieldT, typename TagT>
    using field
        = meta::attribute
                <FieldT, meta::annotation_set
                    <annotation::field        ,
                     annotation::dynamic_attr ,
                     annotation::public_attr  ,
                     annotation::tag<TagT>>>  ;

    template <typename FieldT, typename TagT>
    using static_field
        = meta::attribute
                <FieldT, meta::annotation_set
                    <annotation::field        ,
                     annotation::static_attr  ,
                     annotation::public_attr>>;

    template <auto Method, typename TagT>
    using method
        = meta::attribute
                <void, meta::annotation_set
                    <annotation::method<Method>,
                     annotation::dynamic_attr  ,
                     annotation::public_attr>> ;
    
    template <auto Method, typename TagT>
    using static_method
        = meta::attribute
                <void, meta::annotation_set
                    <annotation::method<Method>,
                     annotation::static_attr   ,
                     annotation::public_attr>> ;

}

    
}