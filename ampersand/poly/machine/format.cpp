#include "format.hpp"

using namespace ampersand::poly::machine;

format_base::format_base
	(instruction& pInstruction)
		: _M_Instruction(pInstruction) {}

format_base::argument_iterator::argument_iterator
	(format_base& pformat, bool pIsFirst) 
		: _M_Iterator
			((pIsFirst)
				? pformat._M_Instruction._M_InstOperand.begin()
				: pformat._M_Instruction._M_InstOperand.end  ()) {}

format_base::argument_iterator&
	format_base::argument_iterator::operator++() {
		++_M_Iterator;
		return *this;
}

format_base::argument_iterator&
	format_base::argument_iterator::operator--() {
		--_M_Iterator;
		return *this;
}

format_base::argument_iterator
	format_base::argument_iterator::operator++(int) {
		++_M_Iterator;
		return *this;
}

format_base::argument_iterator
	format_base::argument_iterator::operator--(int) {
		--_M_Iterator;
		return *this;
}

bool
	format_base::argument_iterator::operator==
		(argument_iterator& pRhs) {
	return _M_Iterator == pRhs._M_Iterator;
}

bool
	format_base::argument_iterator::operator!=
		(argument_iterator& pRhs) {
	return _M_Iterator != pRhs._M_Iterator;
}

operand&
	format_base::argument_iterator::operator*() {
		return *_M_Iterator;
}

format_base::argument_iterator
	format_base::begin_args() {
		return argument_iterator(*this, true);
}

format_base::argument_iterator
	format_base::end_args() {
		return argument_iterator(*this, false);
}