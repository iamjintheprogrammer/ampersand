#include "stack.hpp"

namespace ampersand::diopter {
	stack::stack() {}

	bool stack::push_object(object& pObject) {
		if (pObject.name().empty())
			return false;
		if (_M_Stack.find(pObject.name()) != _M_Stack.end())
			return false;

		_M_Stack.insert
			(std::make_pair(pObject.name(), pObject));
		return true;
	}

	bool stack::pop_object(name_type pName) {
		return
			_M_Stack.erase(pName) == 1;
	}

	object
		stack::find_object(name_type pName) {
			auto ob_found = _M_Stack.find(pName);
			if (ob_found == _M_Stack.end())
				return object{};
			else
				return (*ob_found).second;
	}
}