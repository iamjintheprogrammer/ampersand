#include "fetch.hpp"

using namespace ampersand::poly;

fetch::fetch()
	: _M_Module(poly_binary::current()) {
		_M_Iterator = _M_Module._M_Instruction.begin();
}

machine::instruction& fetch::peek	 () { return *_M_Iterator; }
machine::instruction& fetch::peek_prev() {
	if(_M_Iterator != _M_Module._M_Instruction.begin()) {
		auto it_peek = _M_Iterator;
		   --it_peek;

		return *it_peek;
	}
	else
		return *_M_Iterator;
}

machine::instruction& fetch::peek_next() {
	if(_M_Iterator != _M_Module._M_Instruction.end()) {
		auto it_peek = _M_Iterator;
		   ++it_peek;

		return *it_peek;
	}
	else
		return *_M_Iterator;
}

void fetch::next() { ++_M_Iterator; }
void fetch::prev() { --_M_Iterator; }
fetch::operator bool() {
	return _M_Iterator != _M_Module._M_Instruction.end();
}

fetch_line::fetch_line()
	: _M_Module(poly_binary::current()) {
	_M_ModuleIterator = _M_Module._M_Instruction.begin();
}

fetch_line::iterator::iterator
	(poly_binary::__instruction::iterator pIterator)
		: _M_Iterator(pIterator){
}

fetch_line::iterator&
	fetch_line::iterator::operator++() {
		++_M_Iterator;
		return *this;
}

fetch_line::iterator
	fetch_line::iterator::operator++(int) {
		++_M_Iterator;
		return *this;
}

fetch_line::iterator&
	fetch_line::iterator::operator--() {
		--_M_Iterator;
		return *this;
}

fetch_line::iterator
	fetch_line::iterator::operator--(int) {
		--_M_Iterator;
		return *this;
}

bool
	fetch_line::iterator::operator==
		(iterator& pRhs) {
	return pRhs._M_Iterator == _M_Iterator;
}
bool 
	fetch_line::iterator::operator!=
		(iterator& pRhs) {
	return pRhs._M_Iterator != _M_Iterator;
}

machine::instruction&
	fetch_line::iterator::operator*() {
		return *_M_Iterator;
}

bool fetch_line::parse_next() {
	if (_M_ModuleIterator == _M_Module._M_Instruction.end())
		return false;
	_M_LineInstruction.clear();

	while ((*_M_ModuleIterator).verb() != machine::instruction_verb::leave) {
		if((*_M_ModuleIterator).verb() == machine::instruction_verb::enter) {
			++_M_ModuleIterator;
			continue;
		}

		_M_LineInstruction.push_back(*_M_ModuleIterator);
		++_M_ModuleIterator;
	}

	++_M_ModuleIterator;
	return true;
}

fetch_line::iterator
	fetch_line::begin_point() {
		return iterator(_M_LineInstruction.begin());
}

fetch_line::iterator
	fetch_line::end_point() {
		return iterator(_M_LineInstruction.end());
}