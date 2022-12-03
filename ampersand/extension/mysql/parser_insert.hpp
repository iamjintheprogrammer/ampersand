#pragma once
#include <ampersand/extension/mysql/parser_impl.hpp>
#include <ampersand/extension/mysql/parser_insert_impl.hpp>

namespace ampersand::extension::mysql {
	template
		<typename... TableAttr, typename... RowFieldT>
	class 
		parser
			<schema::syntax::insert
				<schema::table<meta::meta_type<TableAttr...>>, 
					schema::row<RowFieldT...>>>				 {
		using __syntax = schema::syntax::insert<schema::table<meta::meta_type<TableAttr...>>, schema::row<RowFieldT...>>;
			  __syntax _M_Syntax;
	public:
		using syntax_type = __syntax;
		using string_type = std::string;
		using row_type    = schema::row<RowFieldT...>;

		parser(__syntax& pSyntax) : _M_Syntax(pSyntax) {}
		syntax_type& get_syntax()					   { return _M_Syntax; }

		string_type operator()() {
			string_type parsed;
			__parse_insert_impl(_M_Syntax, parsed);

			return parsed;
		}
	};

	template
		<typename... TableAttr>
	class 
		parser
			<schema::syntax::insert
				<schema::table<meta::meta_type<TableAttr...>>>>	 {
		using __syntax = schema::syntax::insert<schema::table<meta::meta_type<TableAttr...>>>;
			  __syntax _M_Syntax;
	public:
		using syntax_type = __syntax;
		using string_type = std::string;
		using row_type    = schema::row<TableAttr...>;

		parser(__syntax& pSyntax) : _M_Syntax(pSyntax) {}
		syntax_type& get_syntax()					   { return _M_Syntax; }

		string_type operator()() {
			string_type parsed;
			__parse_insert_impl(_M_Syntax, parsed);

			return parsed;
		}
	};
}