#include "scope.hpp"

namespace ampersand::diopter {
	scope::scope(scope& pSuper) : _M_Super(&pSuper) { }
	scope::scope() : _M_Super(nullptr) { }

	symbol& scope::get_scoped_symbol() {
		return _M_Symbol;
	}

	stack& scope::get_scoped_stack() {
		return _M_Stack;
	}

	type scope::find_scoped_symbol(name_type pName) { return _M_Symbol.find_symbol(pName); }
	type scope::find_global_symbol(name_type pName) {
		scope* sc_current = this;
		while (sc_current) {
			type sym_found = sc_current->_M_Symbol.find_symbol(pName);
			if (sym_found)
				return sym_found;
			else
				sc_current = sc_current->_M_Super;
		}

		return type{};
	}

	object scope::find_scoped_object(name_type pName) {
		return _M_Stack.find_object(pName);
	}

	object scope::find_global_object(name_type pName) {
		scope* sc_current = this;
		while (sc_current) {
			object ob_found = sc_current->_M_Stack.find_object(pName);
			if (ob_found)
				return ob_found;
			else
				sc_current = sc_current->_M_Super;
		}

		return object{};
	}
}