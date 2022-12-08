#include "declare.hpp"

ampersand::poly::declare::attribute::attribute
	(string_type pTypename, string_type pName)
		: _M_Name(pName),
		  _M_Type(pTypename) {}

typename
	ampersand::poly::declare::attribute::string_type
		ampersand::poly::declare::attribute::name() { return _M_Name; }

typename
	ampersand::poly::declare::attribute::string_type
		ampersand::poly::declare::attribute::type_name() { return _M_Type; }

typename
	ampersand::poly::declare::size_type
		ampersand::poly::declare::attribute_count() {
	return _M_Attributes.size();
}

typename
	ampersand::poly::declare::attribute&
		ampersand::poly::declare::operator[](index_type pIndex) {
	return _M_Attributes[pIndex];
}