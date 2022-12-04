#pragma once
#include <ampersand/schema/type.hpp>
#include <ampersand/schema/type_annotation.hpp>

#include <ampersand/schema/table.hpp>

namespace ampersand::schema::syntax {
	template <typename... AnyType>
	class insert;

	template
		<typename TableString, typename... TableAttr, typename... RowMetaType>
	class
		insert
			<table<TableString, meta::meta_type<TableAttr...>>,
				meta::meta_type<RowMetaType...>>			  {
	public:
		using table_type = table<meta::meta_type<TableAttr...>>;
		insert() = delete;
		insert(table_type& pTable,
					meta::meta_type<RowMetaType...>) 
						: _M_Table(pTable)			{} // For CTAD Support

		table_type& get_table() { return _M_Table; }

	private:
		table_type& _M_Table;
	};

	template
		<typename... TableAttr, typename... RowMetaType,
			typename CondVerb, typename CondLhs, typename CondRhs>
	class
		insert
			<table<meta::meta_type<TableAttr...>>,
				meta::meta_type<RowMetaType...>,
					meta::binary_condition<CondVerb, CondLhs, CondRhs>> {
	public:
		using table_type = table<meta::meta_type<TableAttr...>>;
		insert() = delete;
		insert(table_type& pTable,
				meta::meta_type<RowMetaType...>,
					meta::binary_condition<CondVerb, CondLhs, CondRhs>) 
						: _M_Table(pTable) {}

		table_type& get_table() { return _M_Table; }
	private:
		table_type& _M_Table;
	};

	template <typename Table, typename RowMetaType>
	insert(Table&, RowMetaType) -> insert<Table, RowMetaType>;
	template <typename Table, typename RowMetaType, typename Condition>
	insert(Table&, RowMetaType, Condition) -> insert<Table, RowMetaType, Condition>;
}