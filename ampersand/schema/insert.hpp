#pragma once
#include <tuple>

#include <ampersand/schema/type.hpp>
#include <ampersand/schema/type_annotation.hpp>

#include <ampersand/schema/row.hpp>
#include <ampersand/schema/table.hpp>

namespace ampersand::schema::syntax {
	template <typename... AnyType>
	class insert;

	template
		<typename... TableAttr, typename... RowFieldT>
	class
		insert
			<table<meta::meta_type<TableAttr...>>, row<RowFieldT...>>
		: std::tuple<typename RowFieldT::field_type...>				{
	public:
		using table_type = table<meta::meta_type<TableAttr...>>;
		using row_type   = row  <RowFieldT...>;

		insert() = delete;
		insert(table_type& pTable, row_type) : _M_Table(pTable) {} // For CTAD Support

		table_type& get_table () { return _M_Table; }
		template <typename FieldType>
		auto& operator[](FieldType) {
			return
				std::get
					<boost::mp11::mp_find
						<boost::mp11::mp_list<RowFieldT...>, FieldType>::value>
							(*this);
		}

	private:
		table_type& _M_Table;
	};

	template
		<typename... TableAttr>
	class
		insert
			<table<meta::meta_type<TableAttr...>>>
		: std::tuple<typename TableAttr::attribute_type...>{
	public:
		using table_type = table<meta::meta_type<TableAttr...>>;
		using row_type   = row  <meta::meta_type<TableAttr...>>;

		insert() = delete;
		insert(table_type& pTable) : _M_Table(pTable) {}

		table_type& get_table() { return _M_Table; }
		template <typename FieldType>
		auto& operator[](FieldType) {
			return
				std::get
					<boost::mp11::mp_find
						<boost::mp11::mp_list<TableAttr...>, FieldType>::value>
							(*this);
		}
	private:
		table_type& _M_Table;
	};

	template <typename... TableAttr>
	insert(table<meta::meta_type<TableAttr...>>)
		-> insert<table<meta::meta_type<TableAttr...>>>;

	template <typename... TableAttr, typename... RowAttr>
	insert
		(table<meta::meta_type<TableAttr...>>, row<RowAttr...>)
			-> insert<table<meta::meta_type<TableAttr...>>, row<RowAttr...>>;
}