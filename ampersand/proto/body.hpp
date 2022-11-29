#pragma once
#include <ampersand/proto/body_impl.hpp>

namespace ampersand::proto {
    struct buffer_body     {
    public:
        template <typename AnyType>
        struct attribute_field { using type = void; };

        template <typename... Attributes>
        struct attribute_field<meta::meta_type<Attributes...>> {
            using type = std::uint8_t[__buffer_body_size<Attributes...>::value];
        };

        template <typename Attributes>
        using attribute_field_type = attribute_field<Attributes>::type;

    public:
        template <typename FieldT, typename AttrT, typename MetaT>
        static auto& get(FieldT&& pField, AttrT, MetaT) {
            return
                *reinterpret_cast<typename AttrT::attribute_type*>
                    (reinterpret_cast<std::uint8_t*>(pField)
                        + __buffer_offset<AttrT, MetaT>::value);
        }
    };
}