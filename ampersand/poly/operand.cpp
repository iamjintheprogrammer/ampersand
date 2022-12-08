#include "operand.hpp"

ampersand::poly::operand::operand
	(string_type pTypename, string_type pName)
		: _M_Typename(pTypename),
		  _M_Name	 (pName)    ,
		  _M_Category(category::operand) {}

ampersand::poly::operand::operand()
		: _M_Category(category::void_type) {}

typename
	ampersand::poly::operand::string_type&
		ampersand::poly::operand::name()		 { return _M_Name; }

typename
	ampersand::poly::operand::string_type&
		ampersand::poly::operand::type_name()	 { return _M_Typename; }

typename
	ampersand::poly::operand::category
		ampersand::poly::operand::get_category() { return _M_Category; }