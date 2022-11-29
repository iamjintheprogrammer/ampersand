#pragma once
#include <ampersand/proto/annotation.hpp>

namespace ampersand::proto::fields {
    template <typename FieldT = std::size_t>
    using field            = meta::attribute<FieldT, proto::field>;
    template <typename FieldT = std::size_t, std::size_t N = 16>
    using aligned_field    = meta::attribute<FieldT, proto::field, proto::aligned_field<N>>;
    template <typename FieldT, typename RemapT>
    using remapped_field   = meta::attribute<FieldT, proto::field, proto::remap_field<RemapT>>;
    template <typename FieldT>
    using deprecated_field = meta::attribute<FieldT, proto::field, proto::deprecated_field>;
}