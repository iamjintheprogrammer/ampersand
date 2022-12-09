#include "move.hpp"

namespace ampersand::poly::machine {
	format<format_category::move>::format
		(instruction& pInstruction) 
			: format_base(pInstruction) {
		_M_Op_ArgIter
			= new argument_iterator(this->begin_args());
		
		_M_Op_Destination = &(**_M_Op_ArgIter);
		_M_Op_Source	  = &(**_M_Op_ArgIter); ++(*_M_Op_ArgIter);
	}

	operand&
		format<format_category::move>::source() {
			return *_M_Op_Source;
	}

	operand&
		format<format_category::move>::destination() {
			return *_M_Op_Destination;
	}

	format<format_category::shallow_move>::format
		(instruction& pInstruction) 
			: format_base(pInstruction) {
		_M_Op_ArgIter
			= new argument_iterator(this->begin_args());
		
		_M_Op_Destination = &(**_M_Op_ArgIter);
		_M_Op_Source	  = &(**_M_Op_ArgIter); ++(*_M_Op_ArgIter);
	}

	operand&
		format<format_category::shallow_move>::source() {
			return *_M_Op_Source;
	}

	operand&
		format<format_category::shallow_move>::destination() {
			return *_M_Op_Destination;
	}

	format<format_category::deep_move>::format
		(instruction& pInstruction) 
			: format_base(pInstruction) {
		_M_Op_ArgIter
			= new argument_iterator(this->begin_args());
		
		_M_Op_Destination = &(**_M_Op_ArgIter);
		_M_Op_Source	  = &(**_M_Op_ArgIter); ++(*_M_Op_ArgIter);
	}

	operand&
		format<format_category::deep_move>::source() {
			return *_M_Op_Source;
	}

	operand&
		format<format_category::deep_move>::destination() {
			return *_M_Op_Destination;
	}
}