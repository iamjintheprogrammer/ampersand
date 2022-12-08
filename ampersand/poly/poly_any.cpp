#include "poly_any.hpp"

ampersand::poly::poly_object<>::poly_object()
	: _M_Name("") {  }

ampersand::poly::poly_object<>::~poly_object() {
	if (_M_Name.empty()) {
		auto& cur_module    = poly_module::current();
			  cur_module.push_leave();
	}
	else {
		auto& cur_module = poly_module::current();
			  cur_module.push_enter();
		auto  cur_inst
			= instruction(instruction_verb::ob_delete, "", operand());

		cur_module.push_instruction(cur_inst);
		cur_module.push_leave	   ();
	}
}

ampersand::poly::poly_object<>::poly_object
	(poly_object& pCopy) {
	auto& cur_module = poly_module::current();
		  cur_module.push_enter();
	auto  cur_inst
		= instruction(instruction_verb::move_shallow, "",
			  operand("", _M_Name),
			  operand(pCopy.type_name(), pCopy.name()));

	cur_module.push_instruction(cur_inst);
	cur_module.push_leave();
}

ampersand::poly::poly_object<>::poly_object(poly_object&& pMove) {
	auto& cur_module = poly_module::current();
		  cur_module.push_enter();
	auto  cur_inst
		= instruction(instruction_verb::move_deep, "",
			  operand("", _M_Name),
			  operand(pMove.type_name(), pMove.name()));

	cur_module.push_instruction(cur_inst);
	cur_module.push_leave();
}

typename
	ampersand::poly::poly_object<>::poly_object
		ampersand::poly::poly_object<>::operator[](string_type pName) {
	auto& cur_module = poly_module::current();
		  cur_module.push_enter();
	auto  cur_statement 
		= instruction(instruction_verb::ob_reference, "",
				operand("", "")		,
				operand("", _M_Name),
				operand("", pName)) ;

	cur_module.push_instruction(cur_statement);

	return poly_object<>{};
}

ampersand::poly::poly_object<>&
	ampersand::poly::poly_object<>::operator=
		(poly_object<>& pCopy) {
	auto& cur_module = poly_module::current();
		  cur_module.push_enter();
	auto  cur_inst
		= instruction(instruction_verb::move_shallow, "",
			  operand("", _M_Name),
			  operand(pCopy.type_name(), pCopy.name()));

	cur_module.push_instruction(cur_inst);
	cur_module.push_leave();

	return *this;
}

ampersand::poly::poly_object<>&
	ampersand::poly::poly_object<>::operator=
		(poly_object<>&& pMove) {
	auto& cur_module = poly_module::current();
		  cur_module.push_enter();
	auto  cur_inst
		= instruction(instruction_verb::move_deep, "",
			  operand("", _M_Name),
			  operand(pMove.type_name(), pMove.name()));

	cur_module.push_instruction(cur_inst);
	cur_module.push_leave();

	return *this;
}

typename
	ampersand::poly::poly_object<>::string_type
		ampersand::poly::poly_object<>::type_name() { return ""; }

typename
	ampersand::poly::poly_object<>::string_type&
		ampersand::poly::poly_object<>::name()      { return _M_Name; }