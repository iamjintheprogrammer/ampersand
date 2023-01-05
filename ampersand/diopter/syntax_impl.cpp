#include "syntax_impl.hpp"

namespace ampersand::diopter {
	syntax_impl::syntax_operand_impl::syntax_operand_impl()
		: _M_Impl_Category(category::none) {}
	syntax_impl::syntax_operand_impl::syntax_operand_impl
		(name_type_impl pType, name_type_impl pName)
			: _M_Impl_Operand (pType, pName),
			  _M_Impl_Category(category_impl::operand) {}

	syntax_impl::syntax_operand_impl::syntax_operand_impl
		(meta::primitive_category pType, name_type_impl pName)
			: _M_Impl_Operand (pType, pName),
			  _M_Impl_Category(category_impl::operand) {}

	syntax_impl::syntax_operand_impl::syntax_operand_impl
		(const syntax_operand_impl& pCopy)
			: _M_Impl_Category(pCopy._M_Impl_Category) {
		switch (_M_Impl_Category) {
			case category_impl::syntax:
				_M_Impl_Syntax = pCopy._M_Impl_Syntax;
				break;
			case category_impl::operand:
				_M_Impl_Operand = pCopy._M_Impl_Operand;
				break;
		}
	}

	syntax_impl::syntax_operand_impl::~syntax_operand_impl() {}

	syntax_impl::syntax_operand_impl*
		syntax_impl::operator[](size_type pIndex) {
			if(pIndex >= _M_Impl_Operand.size())
				return nullptr;
			else
				return &_M_Impl_Operand[pIndex];
	}

	syntax_impl::size_type
		syntax_impl::operand_count() {
			return _M_Impl_Operand.size();
	}

	meta::verb
		syntax_impl::get_verb() {
			return _M_Impl_Verb;
	}
}