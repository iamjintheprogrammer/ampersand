#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <tuple>
#include <string>

namespace ampersand::poly {
	template <typename... AnyType>
	struct __name_tuple;
	template <typename... TupleType, typename T, typename... Remaining>
	struct 
		__name_tuple
			<std::tuple<TupleType...>, T, Remaining...> 
				: __name_tuple
					<std::tuple<TupleType..., std::string>, Remaining...> {};
	template <typename... TupleType, typename T>
	struct 
		__name_tuple
			<std::tuple<TupleType...>, T> {
		using type = std::tuple<TupleType..., std::string>;
	};
}