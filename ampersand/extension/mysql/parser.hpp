#pragma once
#include <ampersand/extension/mysql/parser_select.hpp>
#include <ampersand/extension/mysql/parser_insert.hpp>

#include <string>

namespace ampersand::extension::mysql {
	template <typename StringType, typename Syntax>
	parser(StringType, Syntax)->parser<StringType, Syntax>;
}