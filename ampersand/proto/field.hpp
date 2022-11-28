#pragma once
#include <ampersand/meta/meta.hpp>

namespace ampersand::proto::annotation {
    struct field : meta::annotation {};
}

namespace ampersand::proto::attribute {
    template <typename FieldT = std::size_t>
    using field = meta::attribute<FieldT, meta::annotation_set<proto::annotation::field>>;
}