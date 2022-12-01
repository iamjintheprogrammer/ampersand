#pragma once
#include <ampersand/extension/mysql/reader_impl.hpp>

namespace ampersand::extension::mysql {
	template <typename... AnyType>
	class reader;

	template <typename... Attributes>
	class reader
		<table<meta::meta_type<Attributes...>>> {
		using __result = sql::ResultSet*;
	public:
		using table_type = table <meta::meta_type<Attributes...>>;
		class iterator
			: std::iterator
					<std::output_iterator_tag,
					 meta::meta_object
					<meta::body::tuple, meta::meta_type<Attributes...>>> {
			__result _M_Iterator_Base;
			iterator(__result pResult) : _M_Iterator_Base(pResult) {}
		
		public:
			iterator& operator++() {
				if (!_M_Iterator_Base)		   return *this;
				if (!_M_Iterator_Base->next()) _M_Iterator_Base = nullptr;

				return *this;
			}

			iterator  operator++(int) {
				if (!_M_Iterator_Base)		   return *this;
				if (!_M_Iterator_Base->next()) _M_Iterator_Base = nullptr;

				return *this;
			}
			value_type operator* () {
				meta::meta_object
					<meta::body::tuple, meta::meta_type<Attributes...>>
						sql_result;
				
				__read(sql_result, _M_Iterator_Base);
				return sql_result;
			}

			bool operator==(iterator& pRhs) { return pRhs._M_Iterator_Base == _M_Iterator_Base; }
			bool operator!=(iterator& pRhs) { return pRhs._M_Iterator_Base != _M_Iterator_Base; }
		};
		
	public:
		 reader(connection&, table_type&);
		~reader();

	public:
		iterator begin() { return iterator(_M_RdBase); }
		iterator end  () { return iterator(nullptr)  ; }

	private:
		table_type& _M_RdTable;
		__result    _M_RdBase ;
	};

	template <typename... Attribute>
	reader<table<meta::meta_type<Attribute...>>>::reader
		(connection& pRdConn, table_type& pRdTable) : _M_RdTable(pRdTable) {
		std::string sql_query("SELECT * FROM ");
					sql_query += pRdTable.name();

		auto sql_statement = pRdConn._M_Base->createStatement();
		_M_RdBase			= sql_statement->executeQuery(sql_query.c_str());
	}

	
}