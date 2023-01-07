#include "function.hpp"

namespace ampersand::diopter {
	function::function()
		: _M_Impl_Type(function_type_impl::none) { }

	object function::get_return_value() {
		return _M_Impl_Return;
	}

	object function::get_argument(std::size_t pIndex) {
		if (pIndex >= _M_Impl_Arguments.size())
			return object{};
		else
			return _M_Impl_Arguments[pIndex];
	}

	std::size_t function::get_argument_count() {
		return _M_Impl_Arguments.size();
	}

	syntax function::get_syntax(std::size_t pIndex) {
		if (pIndex >= _M_Impl_Arguments.size())
			return syntax{};
		else
			return _M_Impl_Syntax[pIndex];
	}

	std::size_t function::get_syntax_count() {
		return _M_Impl_Syntax.size();
	}

	function::operator bool() {
		return _M_Impl_Type != function_type_impl::none;
	}


}