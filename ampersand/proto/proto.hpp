#pragma once
#include <ampersand/proto/buffer.hpp>
#include <ampersand/proto/field.hpp>
#include <ampersand/proto/size.hpp>

#include <ampersand/proto/address/v4.hpp>

namespace ampersand::proto {
    template <typename FieldT = std::size_t> inline constexpr attribute::field        <FieldT> field        {};
    template <typename SizeT  = std::size_t> inline constexpr attribute::size         <SizeT>  size         {};
    template <typename SizeT  = std::size_t> inline constexpr attribute::received_size<SizeT>  received_size{};
    template <typename SizeT  = std::size_t> inline constexpr attribute::sent_size    <SizeT>  sent_size    {};

    inline constexpr attribute::v4 v4          {};
    inline constexpr attribute::v4 v4_sender   {};
    inline constexpr attribute::v4 v4_receiver {};
}