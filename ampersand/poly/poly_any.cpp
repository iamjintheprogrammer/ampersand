#include "poly_any.hpp"

ampersand::poly::poly_object<>::poly_object()
	: _M_Operand("", "") {  }

ampersand::poly::poly_object<>::~poly_object() {
	machine::operand::object op_this("", "");
	_M_Operand.get_operand(op_this);

	if (op_this.name().empty()) {
		auto& cur_module    = poly_binary::current();
			  cur_module.push_leave();
	}
	else {
		auto& cur_module = poly_binary::current();
			  cur_module.push_enter		   ();
			  cur_module.push_object_delete(_M_Operand);
			  cur_module.push_leave		   ();
	}
}

ampersand::poly::poly_object<>::poly_object
	(poly_object& pCopy) {
	auto& cur_module = poly_binary::current();
		  cur_module.push_enter		  ();
		  cur_module.push_shallow_move(_M_Operand, pCopy._M_Operand);
		  cur_module.push_leave		  ();
}

ampersand::poly::poly_object<>::poly_object(poly_object&& pMove) {
	auto& cur_module = poly_binary::current();
		  cur_module.push_enter		  ();
		  cur_module.push_shallow_move(_M_Operand, pMove._M_Operand);
		  cur_module.push_leave		  ();
}

typename
	ampersand::poly::poly_object<>::poly_object
		ampersand::poly::poly_object<>::operator[](const char* pName) {
	machine::operand::object op_this  ("", "");
	machine::operand		 op_return("", ""),
							 op_key   (pName);
	auto& cur_module = poly_binary::current();
		  cur_module.push_enter();
		  cur_module.push_object_reference
			  (_M_Operand, op_return, op_key);
	return poly_object<>{};
}

ampersand::poly::poly_object<>&
	ampersand::poly::poly_object<>::operator=
		(poly_object<>& pCopy) {
	auto& cur_module = poly_binary::current();
		  cur_module.push_enter		  ();
		  cur_module.push_shallow_move(_M_Operand, pCopy._M_Operand);
		  cur_module.push_leave		  ();

	return *this;
}

ampersand::poly::poly_object<>&
	ampersand::poly::poly_object<>::operator=
		(poly_object<>&& pMove) {
	auto& cur_module = poly_binary::current();
		  cur_module.push_enter();
		  cur_module.push_move (_M_Operand, pMove._M_Operand);
		  cur_module.push_leave();

	return *this;
}