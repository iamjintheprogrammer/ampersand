#include "primitive_operator.hpp"

namespace ampersand::poly::machine {
	format<format_category::primitive_operator>::format
		(instruction& pInstruction) : format_base(pInstruction) {
		_M_Op_ArgIter
			= new argument_iterator(this->begin_args());

		_M_Op_Return = &(**_M_Op_ArgIter); ++(*_M_Op_ArgIter);
		_M_Op_Left   = &(**_M_Op_ArgIter); ++(*_M_Op_ArgIter);
		_M_Op_Right  = &(**_M_Op_ArgIter);
	}

	format<format_category::primitive_operator>::~format() {
		delete _M_Op_ArgIter;
	}

	operand&
		format<format_category::primitive_operator>::return_operand() {
			return *_M_Op_Return;
	}

	operand&
		format<format_category::primitive_operator>::left() {
			return *_M_Op_Left;
	}

	operand&
		format<format_category::primitive_operator>::right() {
			return *_M_Op_Right;
	}

	instruction_verb
		format<format_category::primitive_operator>::verb() {
			return this->_M_Instruction._M_InstVerb;
	}
}