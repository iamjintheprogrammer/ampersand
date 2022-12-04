#pragma once
#include <ampersand/extension/mysql/parser_impl.hpp>
#include <ampersand/extension/mysql/parser_insert_impl.hpp>

namespace ampersand::extension::mysql {
	template
		<typename StringType, typename TableType, typename RowType>
	class 
		parser<StringType, schema::syntax::insert<TableType, RowType>> {
		using __syntax = schema::syntax::insert<TableType, RowType>;
			  __syntax& _M_Syntax;
	public:
		using syntax_type = __syntax  ;
		using string_type = StringType;

		parser(__syntax& pSyntax) : _M_Syntax(pSyntax) {}
		syntax_type& get_syntax() { return _M_Syntax; }
		string_type  operator()() {
			string_type parsed;
			__parse_insert_impl(_M_Syntax, parsed);

			return parsed;
		}
	};

	template
		<typename StringType,
			typename TableType, typename RowType, typename Condition>
	class 
		parser
			<StringType, schema::syntax::insert<TableType, RowType, Condition>>	 {
		using __syntax = schema::syntax::insert<TableType, RowType, Condition>;
			  __syntax& _M_Syntax;
	public:
		using syntax_type = __syntax  ;
		using string_type = StringType;

		parser(__syntax& pSyntax) : _M_Syntax(pSyntax) {}
		syntax_type& get_syntax()					   { return _M_Syntax; }

		string_type operator()() {
			string_type parsed;
			__parse_insert_impl(_M_Syntax, parsed);

			return parsed;
		}
	};
}