#pragma once
#include <ampersand/meta/meta.hpp>

namespace ampersand::proto::annotation {
    struct field : meta::annotation {};
}

namespace ampersand::proto::attribute {
    template <typename FieldT>
    using field = meta::attribute<FieldT, meta::annotation_set<proto::annotation::field>>;
}