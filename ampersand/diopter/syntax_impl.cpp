#include "syntax_impl.hpp"

namespace ampersand::diopter {
	syntax_impl::syntax_operand_impl::syntax_operand_union_impl::syntax_operand_union_impl
		(name_type_impl pType, name_type_impl pName)
			: u_operand(pType, pName) {}

	syntax_impl::syntax_operand_impl::syntax_operand_union_impl::syntax_operand_union_impl
		(meta::primitive_category pType, name_type_impl pName)
			: u_operand(pType, pName) {}

	syntax_impl::syntax_operand_impl::syntax_operand_union_impl::~syntax_operand_union_impl() {}

	syntax_impl::syntax_operand_impl::syntax_operand_impl
		(name_type_impl pType, name_type_impl pName)
			: _M_Impl		  (pType, pName),
			  _M_Impl_Category(category_impl::operand) {}

	syntax_impl::syntax_operand_impl::syntax_operand_impl
		(meta::primitive_category pType, name_type_impl pName)
			: _M_Impl		  (pType, pName),
			  _M_Impl_Category(category_impl::operand) {}

	syntax_impl::syntax_operand_impl::~syntax_operand_impl() {}
}