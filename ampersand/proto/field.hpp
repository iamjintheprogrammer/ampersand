#pragma once
#include <ampersand/proto/annotation.hpp>

namespace ampersand::proto::fields {
    template <typename FieldT = std::size_t>
    using field_t            = meta::attribute<FieldT, proto::field>;
    template <typename FieldT = std::size_t, std::size_t N = 16>
    using aligned_field_t    = meta::attribute<FieldT, proto::field, proto::aligned_field<N>>;
    template <typename FieldT, typename RemapT>
    using remapped_field_t   = meta::attribute<FieldT, proto::field, proto::remap_field<RemapT>>;
    template <typename FieldT>
    using deprecated_field_t = meta::attribute<FieldT, proto::field, proto::deprecated_field>;

    template <typename FieldT>
    using receive_size_field_t = meta::attribute<FieldT, proto::field, proto::receive_size>;
    template <typename FieldT>
    using send_size_field_t    = meta::attribute<FieldT, proto::field, proto::send_size>;

    template <typename FieldT>
    using receive_address_field_t = meta::attribute<FieldT, proto::field, proto::receive_address>;
    template <typename FieldT>
    using send_address_field_t    = meta::attribute<FieldT, proto::field, proto::send_address>;

    template <typename FieldT = std::size_t>
    inline constexpr field_t<FieldT>                  field            {};
    template <typename FieldT = std::size_t, std::size_t N = 16>
    inline constexpr aligned_field_t<FieldT, N>       aligned_field    {};
    template <typename FieldT, typename RemapT>
    inline constexpr remapped_field_t<FieldT, RemapT> remapped_field   {};
    template <typename FieldT>
    inline constexpr deprecated_field_t<FieldT>       deprecated_field {};

    template <typename FieldT>
    inline constexpr receive_size_field_t<FieldT>     receive_size_field {};
    template <typename FieldT>
    inline constexpr send_size_field_t<FieldT>        send_size_field    {};
}