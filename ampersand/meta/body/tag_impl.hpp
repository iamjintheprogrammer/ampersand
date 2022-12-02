#pragma once
#include <tuple>
#include <string>

#include <ampersand/meta/meta.hpp>

namespace ampersand::meta::body {
	template <typename... AnyType>
	struct __tag_name_table_impl;
	
	template <typename AttrT, typename... Remaining, typename... TupleType>
	struct
		__tag_name_table_impl
			<std::tuple<TupleType...>, AttrT, Remaining...> {
		using type
			= __tag_name_table_impl
				<std::tuple<TupleType..., std::string>, Remaining...>::type;
	};

	template <typename AttrT, typename... TupleType>
	struct
		__tag_name_table_impl
			<std::tuple<TupleType...>, AttrT> {
		using type = std::tuple<TupleType..., std::string>;
	};

	template <typename... AnyType>
	using __tag_name_table = __tag_name_table_impl<std::tuple<>, AnyType...>::type;

	template <typename... AnyType>
	struct __tag_attribute_table_impl;

	template <typename... AttrT>
	struct __tag_attribute_table_impl<meta::meta_type<AttrT...>> {
		using type = std::tuple<AttrT...>;
	};

	template <typename MetaType>
	using __tag_attribute_table = __tag_attribute_table_impl<MetaType>::type;

	template <typename... AnyType>
	struct __tag_table;

	template <typename... AttrT>
	struct __tag_table<meta::meta_type<AttrT...>> {
		using __meta = meta::meta_type<AttrT...>;
		
		__tag_attribute_table<__meta>	   attr_table;
		__tag_name_table	 <__meta> attr_name_table;
	};
}