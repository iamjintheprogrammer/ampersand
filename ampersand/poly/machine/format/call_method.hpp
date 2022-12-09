#pragma once
#include <ampersand/poly/machine/instruction.hpp>

#include <ampersand/poly/machine/format.hpp>
#include <ampersand/poly/machine/format_category.hpp>

namespace ampersand::poly::machine {
	template <>
	class format<format_category::call_method>
		: private format_base {
		argument_iterator* _M_Op_ArgIter ;
		operand*		   _M_Op_Return  ,
			   *		   _M_Op_Entry   ,
			   *		   _M_Op_Instance;
	public:
		using string_type = std::string;
		format (instruction&);
		~format();

	public:
		operand&    return_operand();
		operand&    instance	  ();
		string_type entry_name    ();

	public:
		argument_iterator argument_begin();
		argument_iterator argument_end  ();
	};
}