#pragma once
#include <ampersand/schema/type.hpp>
#include <ampersand/schema/type_annotation.hpp>

#include <ampersand/schema/row.hpp>
#include <ampersand/schema/table.hpp>

#include <ampersand/schema/condition.hpp>

namespace ampersand::schema::syntax {
	template <typename... AnyType>
	class select;

	template 
		<typename CondVerb, typename LCond, typename RCond, 
			typename... TableAttr,  typename... RowFieldT> // For SELECT (Field1), (Field2), ... FROM ...
	class
		select <table<meta::meta_type<TableAttr...>>			,
				row  <RowFieldT...>					,
				syntax::binary_condition<CondVerb, LCond, RCond>> {
	public:
		using condition  = syntax::binary_condition<CondVerb, LCond, RCond>;
		using table_type = table<meta::meta_type<TableAttr...>>;
		using row_type   = row  <RowFieldT...>;

		select() = delete;
		select(table_type& pTable, row_type, condition)
			: _M_Table(pTable) {  }

		table_type& get_table() { return _M_Table; }

	private:
		table_type& _M_Table;
	};

	template
		<typename CondVerb, 
			typename LCond, typename RCond, 
				typename... TableAttr> // For SELECT * FROM ...
	class
		select 
			<table<meta::meta_type<TableAttr...>>				,
				syntax::binary_condition<CondVerb, LCond, RCond>> {
	public:
		using condition  = syntax::binary_condition<CondVerb, LCond, RCond>;
		using table_type = table<meta::meta_type<TableAttr...>>;
		using row_type	 = row  <field<TableAttr>...>;

		select() = delete;
		select(table_type& pRow, condition)
			: _M_Table(pRow) {}

		table_type& get_table() { return _M_Table; }

	private:
		table_type& _M_Table;
	};

	template <typename... TableAttr>
	class
		select
			<table<meta::meta_type<TableAttr...>>> {
	public:
		using table_type = table<meta::meta_type<TableAttr...>>;
		using row_type	 = row  <field<TableAttr>...>;

		select() = delete;
		select(table_type& pRow) : _M_Table(pRow) {}

		table_type& get_table() { return _M_Table; }

	private:
		table_type& _M_Table;
	};

	template 
		<typename... TableAttr, typename... RowFieldT> // For SELECT (Field1), (Field2), ... FROM ...
	class
		select 
			<table<meta::meta_type<TableAttr...>>, row<RowFieldT...>> {
	public:
		using table_type = table<meta::meta_type<TableAttr...>>;
		using row_type   = row<RowFieldT...>;

		select() = delete;
		select(table_type& pTable, row_type)
			: _M_Table(pTable) {  }

		table_type& get_table() { return _M_Table; }

	private:
		table_type& _M_Table;
	};

	template 
		<typename... TableAttr,
			typename CondVerb, typename LCond, typename RCond>
	select
		(table<meta::meta_type<TableAttr...>>&, 
				syntax::binary_condition<CondVerb, LCond, RCond>)
		-> select
			<table<meta::meta_type<TableAttr...>>, 
				syntax::binary_condition<CondVerb, LCond, RCond>>;
	template 
		<typename... TableAttr, typename... RowFieldT,
			typename CondVerb, typename LCond, typename RCond>
	select
		(table<meta::meta_type<TableAttr...>>&, row<RowFieldT...>&,
				syntax::binary_condition<CondVerb, LCond, RCond>)
		-> select
			<table<meta::meta_type<TableAttr...>>, 
				row<RowFieldT...>, 
					syntax::binary_condition<CondVerb, LCond, RCond>>;

	template 
		<typename... TableAttr, typename... RowFieldT>
	select
		(table<meta::meta_type<TableAttr...>>&, row<RowFieldT...>&)
		-> select
			<table<meta::meta_type<TableAttr...>>, row<RowFieldT...>>;

	template 
		<typename... TableAttr>
	select
		(table<meta::meta_type<TableAttr...>>&s)
		-> select
			<table<meta::meta_type<TableAttr...>>>;
}