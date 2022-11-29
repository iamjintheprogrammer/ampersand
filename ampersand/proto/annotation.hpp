#pragma once
#include <ampersand/meta/annotation.hpp>
#include <ampersand/meta/attribute.hpp>

namespace ampersand::proto {
    struct                                         field : meta::annotation {};
    template <std::size_t Align> struct    aligned_field : meta::annotation { static constexpr std::size_t value = Align; };
    template <typename T>        struct      remap_field : meta::annotation { typedef T type; };
                                 struct deprecated_field : meta::annotation {};

    template <typename T, std::size_t Min, std::size_t Max>
    struct resizable_field : meta::annotation {
        std::size_t 
            minimum_size = Min,
            maximum_size = Max;
    };
}