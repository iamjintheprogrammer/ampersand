#include "call.hpp"

namespace ampersand::poly::machine {
	format<format_category::call>::format
		(instruction& pInstruction) : format_base(pInstruction) {
		_M_Op_ArgIter
			= new argument_iterator(this->begin_args());
		
		_M_Op_Entry  = &(**_M_Op_ArgIter); ++(*_M_Op_ArgIter);
		_M_Op_Return = &(**_M_Op_ArgIter); ++(*_M_Op_ArgIter);
	}

	format<format_category::call>::~format() {
		delete _M_Op_ArgIter;
	}

	operand&
		format<format_category::call>::return_operand() {
			return *_M_Op_Return;
	}

	format<format_category::call>::string_type
		format<format_category::call>::entry_name() {
			operand::constant name("");
			std::string		  name_str;
			(*_M_Op_Entry).get_operand(name);

			name.get_value(name_str);
			return		   name_str ;
	}

	format<format_category::call>::argument_iterator
		format<format_category::call>::argument_begin() {
			return *_M_Op_ArgIter;
	}

	format<format_category::call>::argument_iterator
		format<format_category::call>::argument_end() {
			return this->end_args();
	}
}