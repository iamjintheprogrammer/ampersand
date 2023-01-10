#pragma once
#include <ampersand/diopter/syntax/syntax.hpp>
#include <ampersand/diopter/syntax/syntax_element.hpp>
#include <ampersand/diopter/syntax/syntax_element_constant.hpp>
#include <ampersand/diopter/syntax/syntax_element_object.hpp>

#include <ampersand/diopter/type.hpp>
#include <ampersand/diopter/type_compound.hpp>
#include <ampersand/diopter/type_compound_nested.hpp>
#include <ampersand/diopter/type_function.hpp>
#include <ampersand/diopter/type_function_argument.hpp>

#include <ampersand/diopter/symbol.hpp>
#include <ampersand/diopter/symbol_result.hpp>

namespace ampersand::diopter::describe {
	class function {
		diopter::symbol impl_symbol;

		function(diopter::symbol&, meta::concepts::meta_dynamic_method auto&);
		function(diopter::symbol&, meta::concepts::meta_static_method  auto&);
	public:
		function(diopter::symbol&, meta::concepts::meta_function auto&);
		
	};
}