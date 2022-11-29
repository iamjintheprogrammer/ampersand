#pragma once
#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/body/raw_impl.hpp>

namespace ampersand::meta::body {
    struct raw {
    public:
        template <typename MetaType>
        struct attribute_field {
            using type = std::uint8_t[__raw_size_v<MetaType>];
        };

        template <typename MetaType>
        using attribute_field_type = typename attribute_field<MetaType>::type;
    };
}