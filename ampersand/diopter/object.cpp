#include "object.hpp"

namespace ampersand::diopter {
	object::object(name_type pName, type& pType)
		: _M_Type(pType),
		  _M_Name(pName) {}

	object::~object() { }

	type		      object::type_of() { return _M_Type; }
	object::name_type object::name   () { return _M_Name; }

	constant::constant(name_type pName, type& pType)
		: _M_Type(pType),
		  _M_Name(pName) {}

	constant::~constant() { }

	type		        constant::type_of() { return _M_Type; }
	constant::name_type constant::name   () { return _M_Name; }
}