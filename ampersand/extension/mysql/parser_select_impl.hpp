#pragma once
#include <ampersand/extension/mysql/parser_binary_impl.hpp>

namespace ampersand::extension::mysql {
		template
		<typename... AttrT, typename... RowFieldT,
				typename CondVerb, typename LCond, typename RCond>
	void
		__parse_select_impl
			(schema::syntax::select
				<schema::table<meta::meta_type<AttrT...>>,
					schema::row<RowFieldT...>,
						schema::syntax::binary_condition<CondVerb, LCond, RCond>>& pSelect,
			 std::string& pParsed) {
		pParsed += "SELECT ";
		[&pParsed, &pSelect] <std::size_t... RowIdx>
			(std::index_sequence<RowIdx...>) {
				((pParsed += (pSelect.get_table()[typename RowFieldT::field_meta_type{}] + ",")), ...);
		}(std::make_index_sequence<sizeof...(RowFieldT)>{});

		pParsed.pop_back();
		pParsed += " FROM "
				+  pSelect.get_table().name()
				+  " WHERE ";

		__parse_binary_condition
			(pSelect.get_table(),
				schema::syntax::binary_condition<CondVerb, LCond, RCond>{},
					pParsed);
	}

	template
		<typename... AttrT,
			typename CondVerb, typename LCond, typename RCond>
	void
		__parse_select_impl
			(schema::syntax::select
				<schema::table<meta::meta_type<AttrT...>>,
					schema::syntax::binary_condition<CondVerb, LCond, RCond>>& pSelect,
			 std::string& pParsed) {
		pParsed += "SELECT * FROM ";
		pParsed += pSelect.get_table().name()
				+  " WHERE ";
		
		__parse_binary_condition
			(pSelect.get_table(),
				schema::syntax::binary_condition<CondVerb, LCond, RCond>{},
					pParsed);
	}

	template
		<typename... AttrT, typename... RowFieldT>
	void
		__parse_select_impl
			(schema::syntax::select
				<schema::table<meta::meta_type<AttrT...>>,
					schema::row<RowFieldT...>>& pSelect,
			 std::string& pParsed) {
		pParsed += "SELECT ";
		[&pParsed, &pSelect] <std::size_t... RowIdx>
			(std::index_sequence<RowIdx...>) {
				((pParsed += (pSelect.get_table()[typename RowFieldT::field_meta_type{}] + ",")), ...);
		}(std::make_index_sequence<sizeof...(RowFieldT)>{});

		pParsed.pop_back();
		pParsed += " FROM "
				+  pSelect.get_table().name();
	}

	template
		<typename... AttrT>
	void
		__parse_select_impl
			(schema::syntax::select
				<schema::table<meta::meta_type<AttrT...>>>& pSelect,
			 std::string& pParsed) {
		pParsed += "SELECT * FROM ";
		pParsed += pSelect.get_table().name();
	}
}