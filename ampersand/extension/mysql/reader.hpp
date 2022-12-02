#pragma once
#include <ampersand/extension/mysql/reader_impl.hpp>
#include <iostream>

namespace ampersand::extension::mysql {
	template <typename... AnyType>
	class reader;

	template <typename BodyT, typename ParserType>
	class reader <BodyT, ParserType> {
		using __result = sql::ResultSet*;
			  __result _M_RdBase;
	public:
		using parser_type = ParserType;
		using value_type  = meta::meta_object<BodyT, typename parser_type::row_type::row_meta_type>;

		class iterator
			: public std::iterator<std::output_iterator_tag, value_type> {
			__result _M_Iterator_Base;

		public:
			iterator(reader& pResult) : _M_Iterator_Base(pResult._M_RdBase) {}
			iterator()				  : _M_Iterator_Base(nullptr)			{}
		
		public:
			iterator&  operator++() {
				if (!_M_Iterator_Base)						 return *this;
				if (!_M_Iterator_Base->next()) _M_Iterator_Base = nullptr;

				return *this;
			}

			iterator   operator++(int) {
				if (!_M_Iterator_Base)						 return *this;
				if (!_M_Iterator_Base->next()) _M_Iterator_Base = nullptr;

				return *this;
			}

			value_type operator* () {
				value_type sql_result;

				__read(sql_result, _M_Iterator_Base);
				return sql_result;
			}

			bool operator==(iterator& pRhs) {
				return pRhs._M_Iterator_Base == _M_Iterator_Base;
			}

			bool operator!=(iterator& pRhs) {
				return pRhs._M_Iterator_Base != _M_Iterator_Base;
			}
		};
		
	public:
		 reader(BodyT, connection&, parser_type&);
		~reader()						 {  }
	};

	template <typename BodyT, typename Connection, typename Parser>
	reader(BodyT, Connection, Parser) -> reader<BodyT, Parser>;

	template <typename BodyT, typename ParserType>
	reader<BodyT, ParserType>::reader
		(BodyT, connection& pRdConn, parser_type& pRdParser) {
		auto		sql_statement = pRdConn._M_Base->createStatement();
		_M_RdBase = sql_statement->executeQuery(pRdParser().c_str());
		_M_RdBase->next();
	}
}