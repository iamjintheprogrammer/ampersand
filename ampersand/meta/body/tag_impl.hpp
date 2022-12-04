#pragma once
#include <tuple>
#include <string>

#include <ampersand/meta/meta.hpp>

namespace ampersand::meta::body {
	template <typename... T>
	struct __tag_meta_to_mp11;

	template <typename... MetaAttr>
	struct __tag_meta_to_mp11<meta_type<MetaAttr...>> {
		using						 type  = boost::mp11::mp_list<MetaAttr...>;
		static constexpr std::size_t count = sizeof...(MetaAttr);
	};

	template <typename... AnyType>
	struct __tag_name_table_impl;
	
	template <typename KeyT, typename AttrT, typename... Remaining, typename... TupleType>
	struct
		__tag_name_table_impl
			<KeyT, std::tuple<TupleType...>, AttrT, Remaining...> {
		using type
			= __tag_name_table_impl
				<KeyT, std::tuple<TupleType..., KeyT>, Remaining...>::type;
	};

	template <typename KeyT, typename AttrT, typename... TupleType>
	struct
		__tag_name_table_impl
			<KeyT, std::tuple<TupleType...>, AttrT> {
		using type = std::tuple<TupleType..., KeyT>;
	};

	template <typename KeyT, typename... AnyType>
	using __tag_name_table = typename __tag_name_table_impl<KeyT, std::tuple<>, AnyType...>::type;

	template <typename... AnyType>
	struct __tag_attribute_table_impl;

	template <typename... AttrT>
	struct __tag_attribute_table_impl<meta::meta_type<AttrT...>> {
		using type = std::tuple<typename AttrT::value_type...>;
	};

	template <typename MetaType>
	using __tag_attribute_table = typename __tag_attribute_table_impl<MetaType>::type;

	template <typename... AnyType>
	struct __tag_table;

	template <typename KeyT, typename... AttrT>
	struct __tag_table<KeyT, meta::meta_type<AttrT...>> {
		using __meta = meta::meta_type<AttrT...>;
		
		__tag_attribute_table<__meta>		  attr_table;
		__tag_name_table	 <KeyT, AttrT...> attr_name_table;
	};
}