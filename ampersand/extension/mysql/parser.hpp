#pragma once
#include <ampersand/extension/mysql/parser_impl.hpp>

#include <ampersand/schema/select.hpp>

namespace ampersand::extension::mysql {
	template <typename... AnyType>
	class parser;

	template 
		<typename TableType, 
			typename RowBody, typename... RowField, typename Condition>
	class
		parser
			<schema::syntax::select
				<TableType, schema::row<RowBody, RowField...>, Condition>>    {
		using __syntax = schema::syntax::select<TableType, schema::row<RowBody, RowField...>, Condition>;
			  __syntax& _M_Syntax;
	public:
		using syntax_type = schema::syntax::select<TableType, schema::row<RowBody, RowField...>, Condition>;
		using string_type = std::string;
		using row_type	  = schema::row<RowBody, RowField...>;

		parser(__syntax& pSyntax) : _M_Syntax(pSyntax) {  }
		syntax_type& get_syntax()					   { return _M_Syntax; }

		string_type operator()() {
			string_type					   parsed;
			__parse_select_impl(_M_Syntax, parsed);

			return parsed;
		}
	};

	template 
		<typename TableType, typename Condition>
	class parser<schema::syntax::select<TableType, Condition>> {
		using __syntax = schema::syntax::select<TableType, Condition>;
			  __syntax& _M_Syntax;
	public:
		using syntax_type = schema::syntax::select<TableType, Condition>;
		using string_type = std::string;
		using row_type	  = typename syntax_type::row_type;

		parser(__syntax& pSyntax) : _M_Syntax(pSyntax) {  }

		string_type operator()() {
			string_type					   parsed;
			__parse_select_impl(_M_Syntax, parsed);

			return parsed;
		}
	};

	template 
		<typename TableType, typename RowBody, typename... RowField>
	class 
		parser
			<schema::syntax::select
				<TableType, schema::row<RowBody, RowField...>>>    {
		using __syntax = schema::syntax::select<TableType, schema::row<RowBody, RowField...>>;
			  __syntax& _M_Syntax;
	public:
		using syntax_type = schema::syntax::select<TableType, schema::row<RowBody, RowField...>>;
		using string_type = std::string;
		using row_type	  = schema::row<RowBody, RowField...>;

		parser(__syntax& pSyntax) : _M_Syntax(pSyntax) {  }
		syntax_type& get_syntax()					   { return _M_Syntax; }

		string_type operator()() {
			string_type					   parsed;
			__parse_select_impl(_M_Syntax, parsed);

			return parsed;
		}
	};

	template 
		<typename TableType>
	class parser<schema::syntax::select<TableType>> {
		using __syntax = schema::syntax::select<TableType>;
			  __syntax& _M_Syntax;
	public:
		using syntax_type = schema::syntax::select<TableType>;
		using string_type = std::string;
		using row_type	  = typename syntax_type::row_type;

		parser(__syntax& pSyntax) : _M_Syntax(pSyntax) {  }
		syntax_type& get_syntax()					   { return _M_Syntax; }

		string_type operator()() {
			string_type					   parsed;
			__parse_select_impl(_M_Syntax, parsed);

			return parsed;
		}
	};

	template <typename SyntaxType>
	parser(SyntaxType) -> parser<SyntaxType>;
}