#pragma once
#include <ampersand/proto/annotation_traits.hpp>

namespace ampersand::proto::utility {
    template <typename... T>
    struct field_size;

    template <typename AttrT, typename... Annotations>
    struct field_size<meta::attribute<AttrT, field, Annotations...>> {
        static constexpr std::size_t value = sizeof(AttrT);
    };

    template <typename AttrT, typename RemapT, typename... Annotations>
    struct field_size<meta::attribute<AttrT, field, remap_field<RemapT>, Annotations...>> {
        static constexpr std::size_t value = sizeof(RemapT);
    };
}