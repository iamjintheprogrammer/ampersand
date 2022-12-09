#include "call_method.hpp"
#include <iostream>

namespace ampersand::poly::machine {
	format<format_category::call_method>::format
		(instruction& pInstruction) : format_base(pInstruction) {
		_M_Op_ArgIter
			= new argument_iterator(this->begin_args());
		
		_M_Op_Entry    = &(**_M_Op_ArgIter); ++(*_M_Op_ArgIter);
		_M_Op_Return   = &(**_M_Op_ArgIter); ++(*_M_Op_ArgIter);
		_M_Op_Instance = &(**_M_Op_ArgIter); ++(*_M_Op_ArgIter);
	}

	format<format_category::call_method>::~format() {
		delete _M_Op_ArgIter;
	}

	operand&
		format<format_category::call_method>::return_operand() {
			return *_M_Op_Return;
	}

	format<format_category::call_method>::string_type
		format<format_category::call_method>::entry_name() {
			operand::constant name("");
			(*_M_Op_Entry).get_operand(name);

			return name.get_string_value();
	}

	operand&
		format<format_category::call_method>::instance() {
			return *_M_Op_Instance;
	}

	format<format_category::call_method>::argument_iterator
		format<format_category::call_method>::argument_begin() {
			return *_M_Op_ArgIter;
	}

	format<format_category::call_method>::argument_iterator
		format<format_category::call_method>::argument_end() {
			return this->end_args();
	}
}