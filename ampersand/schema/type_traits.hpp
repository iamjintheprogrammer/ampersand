#pragma once
#include <type_traits>

#include <ampersand/schema/condition.hpp>

#include <ampersand/schema/field.hpp>
#include <ampersand/schema/row.hpp>
#include <ampersand/schema/table.hpp>

namespace ampersand::schema {
	template <typename... AnyType>
	struct is_row						 : std::false_type {};
	template <typename BodyT, typename... FieldT>
	struct is_row<row<BodyT, FieldT...>> : std::true_type  {};
	template <typename... AnyType>
	inline constexpr bool is_row_v = is_row<AnyType...>::value;

	template <typename... AnyType>
	struct is_field												 : std::false_type {};
	template <typename FieldT, typename... FieldAnnotation>
	struct is_field<meta::attribute<FieldT, FieldAnnotation...>> : std::true_type  {};
	template <typename... AnyType>
	inline constexpr bool is_field_v = is_field<AnyType...>::value;

	template <typename... AnyType>
	struct is_table									: std::false_type {};
	template <typename... Attributes>
	struct is_table<meta::meta_type<Attributes...>> : std::true_type  {};
	template <typename... AnyType>
	inline constexpr bool is_table_v = is_table<AnyType...>::value;

	template <typename...AnyType>
	struct is_binary_condition														   : std::false_type {};
	template <typename Verb, typename LField, typename RField>
	struct is_binary_condition<schema::syntax::binary_condition<Verb, LField, RField>> : std::true_type  {};
	template <typename... AnyType>
	inline constexpr bool is_binary_condition_v = is_binary_condition<AnyType...>::value;
}