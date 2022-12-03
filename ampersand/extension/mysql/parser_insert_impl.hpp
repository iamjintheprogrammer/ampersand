#pragma once
#include <ampersand/schema/insert.hpp>

namespace ampersand::extension::mysql {
	template
		<typename... TableAttr, typename... RowFieldT>
	void
		__parse_insert_impl
			(schema::syntax::insert
				<schema::table<meta::meta_type<TableAttr...>>,
					schema::row<RowFieldT...>>& pTable,
			 std::string& pInsert) {
		pInsert += "INSERT INTO (";
		((pInsert += (pTable.get_table()[typename RowFieldT::field_meta_type{}]) + ","), ...);
		
		pInsert.pop_back();
		pInsert += " VALUES ";
		
		((pInsert += (pTable[RowFieldT{}]) + ","), ...);
		pInsert.pop_back();
	}

	template
		<typename... TableAttr>
	void
		__parse_insert_impl
			(schema::syntax::insert
				<schema::table<meta::meta_type<TableAttr...>>>& pTable,
			 std::string& pInsert) {
		using namespace std::string_literals;
		pInsert += "INSERT INTO "
				+  pTable.get_table().name() + " (";
		((pInsert += (pTable.get_table()[TableAttr{}]) + ","), ...);
		
		pInsert.pop_back();
		pInsert += ") VALUES ("s;
		
		((pInsert += std::to_string(pTable[TableAttr{}]) + ","), ...);
		pInsert.pop_back();
		pInsert += ")";
	}
}