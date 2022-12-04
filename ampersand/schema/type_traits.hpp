#pragma once
#include <type_traits>
#include <ampersand/schema/syntax/insert.hpp>
#include <ampersand/schema/syntax/select.hpp>

#include <ampersand/schema/table.hpp>

namespace ampersand::schema {
	template <typename... AnyType>
	struct is_table									: std::false_type {};
	template <typename... Attributes>
	struct is_table<meta::meta_type<Attributes...>> : std::true_type  {};
	template <typename... AnyType>
	inline constexpr bool is_table_v = is_table<AnyType...>::value;

	template <typename... AnyType>
	struct is_select_syntax										   : std::false_type {};
	template <typename Table, typename Row, typename Condition>
	struct is_select_syntax<syntax::select<Table, Row, Condition>> : std::true_type {};
	template <typename Table, typename Row>
	struct is_select_syntax<syntax::select<Table, Row>>			   : std::true_type {};
	
	template <typename... AnyType>
	struct is_insert_syntax										   : std::false_type {};
	template <typename Table, typename Row, typename Condition>
	struct is_insert_syntax<syntax::insert<Table, Row, Condition>> : std::true_type {};
	template <typename Table, typename Row>
	struct is_insert_syntax<syntax::insert<Table, Row>>			   : std::true_type {};
}