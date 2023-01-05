#include "syntax.hpp"

namespace ampersand::diopter {
	syntax::syntax(syntax_impl& pImpl)
		: _M_Impl	  (&pImpl),
		  _M_Impl_Root(false) {}

	syntax::syntax()
		: _M_Impl	  (nullptr),
		  _M_Impl_Root(false)  {  }

	syntax::syntax_operand::syntax_operand
		(syntax_impl::syntax_operand_impl* pImpl)
			: _M_Impl(pImpl)  {}

	syntax::syntax_operand::category
		syntax::syntax_operand::get_category() {
			if(!_M_Impl)
				return category::none;
			else
				return _M_Impl->_M_Impl_Category;
	}

	syntax
		syntax::syntax_operand::get_syntax() {
		if (this->get_category() != category::syntax)
			return syntax {};
		else
			return syntax(*_M_Impl->_M_Impl_Syntax);
	}
	operand
		syntax::syntax_operand::get_operand() {
		if (this->get_category() != category::operand)
			return operand{};
		else
			return _M_Impl->_M_Impl_Operand;
	}

	syntax::syntax_operand::operator bool() {
		return this->get_category() != category::none;
	}

	syntax::syntax_operand
		syntax::operator[](size_type pIndex) {
			return syntax_operand(_M_Impl->operator[](pIndex));
	}
	
	syntax::size_type
		syntax::opreand_count() {
			return _M_Impl->operand_count();
	}

	meta::verb
		syntax::get_verb() {
			return _M_Impl->get_verb();
	}
}