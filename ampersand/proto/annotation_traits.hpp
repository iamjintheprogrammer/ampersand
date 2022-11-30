#pragma once
#include <type_traits>

#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

#include <ampersand/proto/annotation.hpp>

namespace ampersand::proto {
    template <typename T> struct                    is_field        : std::false_type {};
    template <>           struct                    is_field<field> : std::true_type  {};
    template <typename T> inline constexpr bool     is_field_v      = is_field::value;

    template <typename T>    struct                 is_aligned_field                   : std::false_type {};
    template <std::size_t N> struct                 is_aligned_field<aligned_field<N>> : std::true_type  {};
    template <typename T>    inline constexpr bool  is_aligned_field_v = is_aligned_field<T>::value;

    template <typename T> struct                    is_remapped                 : std::false_type {};
    template <typename T> struct                    is_remapped<remap_field<T>> : std::true_type  {};
    template <typename T> inline constexpr bool     is_remapped_v = is_remapped<T>::value;
    
    template <typename T> struct                    is_deprecated                   : std::false_type {};
    template <>           struct                    is_deprecated<deprecated_field> : std::true_type  {};
    template <typename T> inline constexpr bool     is_deprecated_v = is_deprecated<T>::value;

    template <typename T> struct                    is_received_size               : std::false_type {};
    template <>           struct                    is_received_size<receive_size> : std::true_type  {};

    template <typename T> struct                    is_send_size            : std::false_type {};
    template <>           struct                    is_send_size<send_size> : std::true_type  {};

    template <typename T>
    struct is_resizable                               : std::false_type {};
    template <typename T, std::size_t Min, std::size_t Max>
    struct is_resizable<resizable_field<T, Min, Max>> : std::true_type  {};

    template <typename T> struct is_receive_address                  : std::false_type {};
    template <>           struct is_receive_address<receive_address> : std::true_type  {};

    template <typename T> struct is_send_address               : std::false_type {};
    template <>           struct is_send_address<send_address> : std::true_type  {};
}