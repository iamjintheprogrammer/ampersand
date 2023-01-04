#include "symbol.hpp"

namespace ampersand::diopter {
	symbol::symbol() {}
	type symbol::find_symbol (name_type pName) {
		auto sym_found = _M_Table.find(pName);
		
		return
			(sym_found == _M_Table.end())
				? type() 
				: type((*sym_found).second);
	}

	bool symbol::pop_symbol(name_type pName) {
		return _M_Table.erase(pName) == 1;
	}
}