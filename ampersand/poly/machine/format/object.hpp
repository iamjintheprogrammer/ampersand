#pragma once
#include <ampersand/poly/machine/instruction.hpp>

#include <ampersand/poly/machine/format.hpp>
#include <ampersand/poly/machine/format_category.hpp>

namespace ampersand::poly::machine {
	template <>
	class format<format_category::create_object>
		: private format_base {
		argument_iterator* _M_Op_ArgIter ;
		operand*		   _M_Op_Instance;
	public:
		using string_type = std::string;
		format(instruction&);
		~format();

	public:
		string_type type_name();
		string_type  	 name();

	public:
		argument_iterator argument_begin();
		argument_iterator argument_end  ();
	};

	template <>
	class format<format_category::delete_object>
		: private format_base {
		argument_iterator* _M_Op_ArgIter ;
		operand*		   _M_Op_Instance;
	public:
		using string_type = std::string;
		format(instruction&);
		~format();

	public:
		string_type type_name();
		string_type  	 name();
	};

	template <>
	class format<format_category::reference_object>
		: private format_base {
		argument_iterator* _M_Op_ArgIter ;
		operand*		   _M_Op_Instance,
			   *		   _M_Op_Return  ,
			   *		   _M_Op_RefKey  ;
	public:
		using string_type = std::string;
		format(instruction&);
		~format();

	public:
		string_type		 type_name();
		string_type  		  name();
		operand&    return_operand();
		operand&			   key();
	};
}