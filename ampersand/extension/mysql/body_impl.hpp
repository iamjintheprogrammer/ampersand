#pragma once
#include <tuple>
#include <string>
#include <ampersand/meta/meta.hpp>

namespace ampersand::extension::mysql {
	template <typename... AnyType>
	struct __name_tuple_from_meta_impl;

	template <typename AttrT, typename... Remaining, typename... TupleString>
	struct __name_tuple_from_meta_impl<std::tuple<TupleString...>, AttrT, Remaining...> {
		using type
			= __name_tuple_from_meta_impl
					<std::tuple<TupleString..., std::string>, Remaining...>::type;
	};

	template <typename AttrT, typename... TupleString>
	struct __name_tuple_from_meta_impl<std::tuple<TupleString...>, AttrT> {
		using type = std::tuple<TupleString..., std::string>;
	};

	template <typename... Attributes>
	struct __name_tuple_from_meta {
		using type 
			= typename 
				__name_tuple_from_meta_impl
					<std::tuple<>, std::remove_reference_t<Attributes>...>::type;
	};
}