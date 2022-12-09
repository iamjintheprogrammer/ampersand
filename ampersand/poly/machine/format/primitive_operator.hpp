#pragma once
#include <ampersand/poly/machine/instruction.hpp>

#include <ampersand/poly/machine/format.hpp>
#include <ampersand/poly/machine/format_category.hpp>

namespace ampersand::poly::machine {
	template <>
	class format<format_category::primitive_operator>
		: private format_base {
		argument_iterator* _M_Op_ArgIter ;
		instruction_verb   _M_Op_Verb	 ;
		operand*		   _M_Op_Return  ,
			   *		   _M_Op_Left    ,
			   *		   _M_Op_Right   ;
	public:
		using string_type = std::string;
		format(instruction&);
		~format();

	public:
		instruction_verb verb		   ();
		operand&		 return_operand();
		operand&		 left		   ();
		operand&		 right		   ();
	};
}