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

		template <typename... T>
		friend class reader_iterator;
	public:
		using parser_type = ParserType;
		using value_type  = meta::meta_object<BodyT, typename parser_type::row_type::row_meta_type>;
		
	public:
		 reader(BodyT, connection&, parser_type&);
		~reader()								 {  }
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