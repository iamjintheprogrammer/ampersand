#pragma once
#include <cstdint>
#include <cstddef>

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

    public:
        template <typename MetaT, typename FieldT, typename AttrT>
        static constexpr typename AttrT::value_type& get      (FieldT&&, AttrT);
        template <typename MetaT, typename FieldT, typename AttrT>
        static constexpr std::ptrdiff_t              get_index(FieldT&&, AttrT);
    };

    template <typename MetaT, typename FieldT, typename AttrT>
    constexpr typename AttrT::value_type&
        raw::get 
            (FieldT&& pField, AttrT) {
        return
            *reinterpret_cast<typename AttrT::value_type*>
                (reinterpret_cast<std::uint8_t*>(pField) + __raw_offset_v<AttrT, MetaT>);
    }

    template <typename MetaT, typename FieldT, typename AttrT>
    constexpr std::ptrdiff_t
        raw::get_index
            (FieldT&& pField, AttrT) {
        return
            boost::mp11::mp_find
                <typename __raw_meta_to_mp11<MetaT>::type, AttrT>::value;
    }
}

namespace ampersand::meta { inline constexpr body::raw raw_body = body::raw{}; }