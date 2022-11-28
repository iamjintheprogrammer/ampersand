#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/proto/field.hpp>

namespace ampersand::proto::annotation {
    struct any_address : meta::annotation {};
   }

namespace ampersand::proto::attribute {
    template <typename AddrT>
    using any_address = meta::attribute
                            <AddrT,
                             meta::annotation_set
                                <proto::annotation::any_address, proto::annotation::field>>;
}