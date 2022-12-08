#include "decoder.hpp"

using namespace ampersand::poly;

decoder_base::decoder_base
	(instruction& pInstruction)
		: _M_Instruction(pInstruction) {}

decoder_base::argument_iterator::argument_iterator
	(decoder_base& pDecoder, bool pIsFirst) 
		: _M_Iterator
			((pIsFirst)
				? pDecoder._M_Instruction._M_InstOperand.begin()
				: pDecoder._M_Instruction._M_InstOperand.end  ()) {}

decoder_base::argument_iterator&
	decoder_base::argument_iterator::operator++() {
		++_M_Iterator;
		return *this;
}

decoder_base::argument_iterator&
	decoder_base::argument_iterator::operator--() {
		--_M_Iterator;
		return *this;
}

decoder_base::argument_iterator
	decoder_base::argument_iterator::operator++(int) {
		++_M_Iterator;
		return *this;
}

decoder_base::argument_iterator
	decoder_base::argument_iterator::operator--(int) {
		--_M_Iterator;
		return *this;
}

bool
	decoder_base::argument_iterator::operator==
		(argument_iterator& pRhs) {
	return _M_Iterator == pRhs._M_Iterator;
}

bool
	decoder_base::argument_iterator::operator!=
		(argument_iterator& pRhs) {
	return _M_Iterator != pRhs._M_Iterator;
}

operand&
	decoder_base::argument_iterator::operator*() {
		return *_M_Iterator;
}

decoder::decoder
	(instruction& pInstruction)
		: decoder_base(pInstruction) {}

typename
	decoder::string_type
		decoder::function_name() {
	return _M_Instruction._M_InstName;
}

operand&
	decoder::return_operand() {
		return _M_Instruction._M_InstOperand[0];
}

decoder_base::argument_iterator
	decoder_base::begin_args() {
		return 
			argument_iterator { *this, true };
}

decoder_base::argument_iterator
	decoder_base::end_args() {
		return 
			argument_iterator { *this, false };
}