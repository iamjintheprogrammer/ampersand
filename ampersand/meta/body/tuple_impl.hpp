#pragma once
#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/body/raw_impl.hpp>

namespace ampersand::meta::body {
	template <typename... T>
    struct __tuple_meta_to_mp11;

    template <typename... MetaAttr>
    struct __tuple_meta_to_mp11<meta_type<MetaAttr...>> {
        using type = boost::mp11::mp_list<MetaAttr...>;
    };
}