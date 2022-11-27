#pragma once
#include <meta/field.hpp>
#include <meta/attribute.hpp>

namespace ampersand::meta {
	template <typename... T>
	struct push_attribute;

	template <typename... T>
	struct pop_attribute;

	template <typename Attr, typename FieldT, typename... FieldAttr>
	struct push_attribute
				<Attr,
				 field<FieldT, attribute_set<FieldAttr...>>> {
		using type 
			= field<FieldT,
					type_table::push_back<Attr, attribute_set<FieldAttr...>>>;
	};

	template <typename... T>
	using push_attribute_t = typename push_attribute<T...>::type;

	template <typename Attr, typename FieldT, typename... FieldAttr>
	struct pop_attribute
				<Attr,
				 field<FieldT, attribute_set<FieldAttr...>>> {
		using type 
			= field<FieldT, 
					type_table::pop_back<Attr, attribute_set<FieldAttr...>>>;
	};

	template <typename... T>
	using pop_attribute_t = typename pop_attribute<T...>::type;

	
}