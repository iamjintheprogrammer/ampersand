#pragma once
#include <ampersand/schema/type.hpp>
#include <ampersand/schema/type_annotation.hpp>
#include <ampersand/schema/table.hpp>

#include <ampersand/meta/condition.hpp>

namespace ampersand::schema::syntax {
	template <typename... AnyType>
	class select;

	template 
		<typename TableString, typename... TableAttr, typename... RowMetaType,
			typename CondVerb, typename LCond, typename RCond> // For SELECT (Field1), (Field2), ... FROM ...
	class
		select
			<table<TableString, meta::meta_type<TableAttr...>>,
				meta::meta_type<RowMetaType...>,
					meta::binary_condition<CondVerb, LCond, RCond>> {
	public:
		using table_type = table<TableString, meta::meta_type<TableAttr...>>;

		select() = delete;
		select(table_type& pTable,
					meta::meta_type<RowMetaType...>,
						meta::binary_condition<CondVerb, LCond, RCond>)
			: _M_Table(pTable) {  }

		table_type& get_table() { return _M_Table; }

	private:
		table_type& _M_Table;
	};

	template
		<typename TableString, typename... TableAttr, typename... RowMetaType> // For SELECT * FROM ...
	class
		select 
			<table<TableString, meta::meta_type<TableAttr...>>,
				meta::meta_type<RowMetaType...>>			  {
	public:
		using table_type = table<TableString, meta::meta_type<TableAttr...>>;

		select() = delete;
		select(table_type& pRow, meta::meta_type<RowMetaType...>) : _M_Table(pRow) {}

		table_type& get_table() { return _M_Table; }

	private:
		table_type& _M_Table;
	};

	template <typename TableType, typename MetaType, typename Condition>
	select(TableType&, MetaType, Condition)-> select<TableType, MetaType, Condition>;
	template <typename TableType, typename MetaType>
	select(TableType&, MetaType)		   -> select<TableType, MetaType>;
}