#pragma once
#include <meta/field.hpp>
#include <meta/attribute.hpp>

namespace ampersand::meta {
	template <typename... T>
	struct __push_field_attribute;

	template <typename T, typename FieldT, typename... FieldAttr>
	struct __push_field_attribute<T, const field<FieldT, attribute_set<FieldAttr...>>> {
		using type = field<FieldT, attribute_set<FieldAttr..., T>>;
	};

	template <typename T, typename FieldT, typename... FieldAttr>
	struct __push_field_attribute<T, field<FieldT, attribute_set<FieldAttr...>>> {
		using type = field<FieldT, attribute_set<FieldAttr..., T>>;
	};

	template <typename... T>
	using  push_field_attribute_t = typename __push_field_attribute<T...>::type;

	template <typename Attr, typename FieldT, typename... FieldAttr>
	constexpr const push_field_attribute_t<Attr, field<FieldT, attribute_set<FieldAttr...>>>&
		push_field_attribute
			(const field<FieldT, attribute_set<FieldAttr...>>& pField) {
		return 
			field<FieldT,
				  push_attribute_t
				  	<Attr, attribute_set<FieldAttr...>>>(pField);
	}

	template <typename Attr, typename FieldT, typename... FieldAttr>
	constexpr auto
		pop_field_attribute
			(const field<FieldT, attribute_set<FieldAttr...>>& pField) {
		return
			field<FieldT,
				  pop_attribute_t
				  	<attribute_set<FieldAttr...>>>(pField);
	}
}