#include "poly_module.hpp"

static thread_local ampersand::poly::poly_module  module_global  = ampersand::poly::poly_module{};
static thread_local ampersand::poly::poly_module* module_current = &module_global;

ampersand::poly::poly_module::poly_module()
	: _M_Prev(module_current) { module_current = this; }

ampersand::poly::poly_module::~poly_module() {
	if (module_current == this)
		return;

	module_current = _M_Prev;
}

ampersand::poly::poly_module&
	ampersand::poly::poly_module::current() { return *module_current; }

void
	ampersand::poly::poly_module::push
		(declare& pDeclare) { _M_Declare.push_back(pDeclare); }

void
	ampersand::poly::poly_module::push_instruction
		(instruction& pStatement) { _M_Instruction.push_back(pStatement); }

void
	ampersand::poly::poly_module::push_enter() {
		instruction inst_begin
			(instruction_verb::enter, "", ampersand::poly::operand());
		_M_Instruction.push_back(inst_begin);
}

void
	ampersand::poly::poly_module::push_leave() {
		instruction stmt_begin
			(instruction_verb::leave, "", ampersand::poly::operand());
		_M_Instruction.push_back(stmt_begin);
}