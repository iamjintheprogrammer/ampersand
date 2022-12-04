#pragma once
#include <ampersand/schema/syntax/insert.hpp>

namespace ampersand::extension::mysql {
	template
		<typename... TableAttr, typename Condition, 
			typename... RowAttr, typename RowBody, typename StringType>
	void
		__parse_insert_impl
			(schema::syntax::insert
				<schema::table<meta::meta_type<TableAttr...>>,
					meta::meta_type<RowAttr...>, Condition>&			 pTable ,
				meta::meta_object<RowBody, meta::meta_type<RowAttr...>>& pRow   ,
					StringType&&										 pInsert) {
		pInsert += "INSERT INTO (";
		((pInsert += (pTable.get_table()[RowAttr{}]) + ","), ...);
		
		pInsert.pop_back();
		pInsert += " VALUES ";
		
		((pInsert += (std::to_string(pRow[RowAttr{}])) + ","), ...);
		pInsert.pop_back();
	}

	template
		<typename... TableAttr, 
			typename... RowAttr, typename RowBody, typename StringType>
	void
		__parse_insert_impl
			(schema::syntax::insert
				<schema::table<meta::meta_type<TableAttr...>>,
					meta::meta_type<RowAttr...>>&						pTable,
				meta::meta_object<RowBody, meta::meta_type<RowAttr...>> pRow  ,
					StringType&&										pInsert) {
		using namespace std::string_literals;
		pInsert += "INSERT INTO "
				+  pTable.get_table().name() + " (";
		((pInsert += (pTable.get_table()[RowAttr{}]) + ","), ...);
		
		pInsert.pop_back();
		pInsert += ") VALUES ("s;
		
		((pInsert += std::to_string(pRow[RowAttr{}]) + ","), ...);
		pInsert.pop_back();
		pInsert += ")";
	}
}