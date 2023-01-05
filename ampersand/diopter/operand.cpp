#include "operand.hpp"

namespace ampersand::diopter {
	operand::operand() : _M_Impl() {}

	operand::operand(const operand& pCopy)
		: _M_Impl(pCopy._M_Impl) {}

	operand::operand(name_type pType, name_type pName)
		: _M_Impl(pType, pName) { }

	operand::operand(meta::primitive_category pCategory, name_type pName)
		: _M_Impl(pCategory, pName) {}

	operand::name_type operand::type_name() { return _M_Impl.type_name(); }
	operand::name_type operand::     name() { return _M_Impl.	  name(); }

	operand& operand::operator=(const operand& pCopy) {
		_M_Impl = pCopy._M_Impl;
		return *this;
	}

	operand::operator bool() {
		return _M_Impl.operator bool();
	}
}