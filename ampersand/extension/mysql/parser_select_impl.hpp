#pragma once
#include <ampersand/extension/mysql/parser_binary_impl.hpp>
#include <ampersand/schema/syntax/select.hpp>

namespace ampersand::extension::mysql {
	template
		<typename TableType, typename... TableAttr, typename... RowFieldT, 
			typename Condition, typename StringType>
	void
		__parse_select_impl
			(schema::syntax::select
				<schema::table<TableType, meta::meta_type<TableAttr...>>,
					meta::meta_type<RowFieldT...>, Condition>& pSelect,
				StringType&&								   pParsed) {
		if constexpr
			(std::is_same_v
				<meta::meta_type<TableAttr...>, meta::meta_type<RowFieldT...>>)
			pParsed += "SELECT * ";
		else {
			  pParsed += "SELECT ";
			((pParsed += (pSelect.get_table()[RowFieldT{}] + ",")), ...);
		}

		pParsed.pop_back();
		pParsed += " FROM "
				+  pSelect.get_table().name()
				+  " WHERE ";

		__parse_binary_condition
			(pSelect.get_table(), Condition{}, pParsed);
	}

	template
		<typename TableType, typename... TableAttr, 
			typename... RowFieldT, typename StringType>
	void
		__parse_select_impl
			(schema::syntax::select
				<schema::table<TableType, meta::meta_type<TableAttr...>>,
					meta::meta_type<RowFieldT...>>& pSelect,
				StringType&& pParsed) {
		if constexpr
			(std::is_same_v
				<meta::meta_type<TableAttr...>, meta::meta_type<RowFieldT...>>)
			pParsed += "SELECT * ";
		else {
			  pParsed += "SELECT ";
			((pParsed += (pSelect.get_table()[RowFieldT{}] + ",")), ...);
			  pParsed.pop_back();
		}

		pParsed += " FROM "
				+  pSelect.get_table().name();
	}
}