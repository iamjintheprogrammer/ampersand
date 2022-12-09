#include "poly_binary.hpp"

static thread_local ampersand::poly::poly_binary  bin_global  = ampersand::poly::poly_binary{};
static thread_local ampersand::poly::poly_binary* bin_current = &bin_global;

ampersand::poly::poly_binary::poly_binary()
	: _M_Prev(bin_current) { bin_current = this; }

ampersand::poly::poly_binary::~poly_binary() {
	if (bin_current == this)
		return;

	bin_current = _M_Prev;
}

ampersand::poly::poly_binary&
	ampersand::poly::poly_binary::current() { return *bin_current; }

void
	ampersand::poly::poly_binary::push_declare
		(declare& pDeclare) { _M_Declare.push_back(pDeclare); }

void
	ampersand::poly::poly_binary::push_instruction
		(machine::instruction& pStatement) { 
	_M_Instruction.push_back(pStatement); 
}

void
	ampersand::poly::poly_binary::push_enter() {
		machine::instruction inst_begin
			(machine::instruction_verb::enter, "", 
				ampersand::poly::machine::operand());
		_M_Instruction.push_back(inst_begin);
}

void
	ampersand::poly::poly_binary::push_leave() {
		machine::instruction stmt_begin
			(machine::instruction_verb::leave, "", ampersand::poly::machine::operand());
		_M_Instruction.push_back(stmt_begin);
}

void
	ampersand::poly::poly_binary::push_object_delete
		(machine::operand& pInstance) {
	_M_Instruction.push_back
			(machine::instruction
				(machine::instruction_verb::ob_delete, pInstance));
}

void
	ampersand::poly::poly_binary::push_object_reference
		(machine::operand& pInstance,
		 machine::operand& pReturn  ,
		 machine::operand& pKey)	{
	_M_Instruction.push_back
			(machine::instruction
				(machine::instruction_verb::ob_reference,
					pInstance, pReturn, pKey));
}

void
	ampersand::poly::poly_binary::push_primitive_operator
		(machine::instruction_verb pVerb  ,
		 machine::operand&		   pReturn,
		 machine::operand&		   pLhs   ,
		 machine::operand&		   pRhs)  {
	_M_Instruction.push_back(machine::instruction(pVerb, pReturn, pLhs, pRhs));
}
void
	ampersand::poly::poly_binary::push_move
		(machine::operand& pDest, machine::operand& pSrc) {
	_M_Instruction.push_back
		(machine::instruction
			(machine::instruction_verb::move, pDest, pSrc));
}

void
	ampersand::poly::poly_binary::push_shallow_move
		(machine::operand& pDest, machine::operand& pSrc) {
	_M_Instruction.push_back
		(machine::instruction
			(machine::instruction_verb::move, pDest, pSrc));
}

void
	ampersand::poly::poly_binary::push_deep_move
		(machine::operand& pDest, machine::operand& pSrc) {
	_M_Instruction.push_back
		(machine::instruction
			(machine::instruction_verb::move, pDest, pSrc));
}