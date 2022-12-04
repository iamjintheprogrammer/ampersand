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
		using value_type
			= meta::meta_object
				<BodyT, typename __parser_value_metatype<parser_type>::type>;
		
	public:
		 reader(BodyT, connection&, parser_type&);
		 reader(BodyT, connection&, parser_type&&);
		~reader()								 {  }
	};

	template
		<typename StringType, typename BodyT, typename MetaType>
	class reader<StringType, meta::meta_object<BodyT, MetaType>> { // No Parser. Unsafe Selection.
		using __result = sql::ResultSet*;
			  __result _M_RdBase;
		template <typename... T>
		friend class reader_iterator;
	public:
		using string_type = StringType;
		using value_type  = meta::meta_object<BodyT, MetaType>;

	public:
		reader(string_type, connection&, meta::meta_object<BodyT, MetaType>);
		reader(string_type, connection&);
		~reader()		   {}
	};

	template <typename BodyT, typename Connection, typename Parser>
	reader(BodyT, Connection, Parser) -> reader<BodyT, Parser>;

	template <typename StringType, typename Connection, typename BodyT, typename... AttrT>
	reader(StringType, Connection, meta::meta_object<BodyT, meta::meta_type<AttrT...>>) 
		-> reader<StringType, meta::meta_object<BodyT, meta::meta_type<AttrT...>>>;

	template <typename BodyT, typename ParserType>
	reader<BodyT, ParserType>::reader
		(BodyT, connection& pRdConn, parser_type& pRdParser) {
		auto		sql_statement = pRdConn._M_Base->createStatement();
		_M_RdBase = sql_statement->executeQuery(pRdParser().c_str());
		if(!_M_RdBase->next())
			_M_RdBase = nullptr;
	}

	template <typename BodyT, typename ParserType>
	reader<BodyT, ParserType>::reader
		(BodyT, connection& pRdConn, parser_type&& pRdParser) {
		auto		sql_statement = pRdConn._M_Base->createStatement();
		_M_RdBase = sql_statement->executeQuery(pRdParser().c_str());
		if(!_M_RdBase->next())
			_M_RdBase = nullptr;
	}

	template
		<typename StringType, typename BodyT, typename MetaType>
		reader<StringType, meta::meta_object<BodyT, MetaType>>::reader
			(string_type pString, connection& pRdConn) {
		auto		sql_statement = pRdConn._M_Base->createStatement();
		_M_RdBase = sql_statement->executeQuery(pString.c_str());
		
		if(!_M_RdBase->next())
			_M_RdBase = nullptr;
	}

	template
		<typename StringType, typename BodyT, typename MetaType>
		reader<StringType, meta::meta_object<BodyT, MetaType>>::reader
			(string_type pString, connection& pRdConn, meta::meta_object<BodyT, MetaType>) {
		auto		sql_statement = pRdConn._M_Base->createStatement();
		_M_RdBase = sql_statement->executeQuery(pString.c_str());
		if(!_M_RdBase->next())
			_M_RdBase = nullptr;
	}
}