#pragma once
#include <ampersand/extension/mysql/parser_impl.hpp>
#include <ampersand/extension/mysql/parser_select_impl.hpp>

namespace ampersand::extension::mysql {
	template 
		<typename StringType, typename TableType, 
			typename RowType, typename Condition>
	class
		parser
			<StringType,
				schema::syntax::select<TableType, RowType, Condition>> {
		using __syntax = schema::syntax::select<TableType, RowType, Condition>;
		using __string = StringType;

			  __syntax& _M_Syntax;
			  __string  _M_Parsed;
	public:
		using syntax_type = __syntax;
		using string_type = __string;

		parser(__string pString, __syntax& pSyntax)
			: _M_Parsed(pString),
			  _M_Syntax(pSyntax)  {  }
		syntax_type& get_syntax() { return _M_Syntax; }
		string_type& operator()() {
			__parse_select_impl(_M_Syntax, _M_Parsed);
			return _M_Parsed;
		}
	};
}