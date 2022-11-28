#pragma once
#include <ampersand/define_constexpr.hpp>
#include <ampersand/meta/meta.hpp>

#include <ampersand/proto/field.hpp>

namespace ampersand::proto::annotation {
    struct size          : meta::annotation {};
    struct received_size : meta::annotation {};
    struct sent_size     : meta::annotation {};

    template <std::size_t SizeValue>
    struct remap_size : meta::annotation { AMPERSAND_CONST_MEMBER(std::size_t, value, SizeValue) };
}

namespace ampersand::proto::attribute {
    template <typename SizeT = std::size_t>
    using size          = meta::attribute<SizeT, 
                          meta::annotation_set<proto::annotation::size,
                                               proto::annotation::field>>;

    template <typename SizeT = std::size_t>
    using received_size = meta::attribute<SizeT,
                          meta::annotation_set<proto::annotation::size         ,
                                               proto::annotation::received_size, 
                                               proto::annotation::field>>      ;

    template <typename SizeT = std::size_t>
    using sent_size     = meta::attribute<SizeT,
                          meta::annotation_set<proto::annotation::size     ,
                                               proto::annotation::sent_size,
                                               proto::annotation::field>>  ;
}