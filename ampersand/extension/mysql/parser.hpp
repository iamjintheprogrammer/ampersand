#pragma once
#include <ampersand/extension/mysql/parser_select.hpp>
#include <ampersand/extension/mysql/parser_insert.hpp>

namespace ampersand::extension::mysql {
	template <typename Syntax>
	parser(Syntax) -> parser<Syntax>;
}