#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/proto/field.hpp>

namespace ampersand::proto::annotation {
    struct v4 : meta::annotation {};
   }

namespace ampersand::proto::attribute {
    template <typename AddrT>
    using v4 = meta::attribute<std::uint32_t,
                               meta::annotation_set
                                    <proto::annotation::v4, 
                                     proto::annotation::field>>;
}