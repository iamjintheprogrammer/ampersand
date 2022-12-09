#pragma once
#include <ampersand/poly/machine/instruction.hpp>

#include <ampersand/poly/machine/format.hpp>
#include <ampersand/poly/machine/format_category.hpp>

namespace ampersand::poly::machine {
	template <>
	class format<format_category::move>
		: private format_base {
		argument_iterator* _M_Op_ArgIter ;
		operand*		   _M_Op_Source		,
			   *		   _M_Op_Destination;
	public:
		using string_type = std::string;
		format(instruction&);

	public:
		operand& source	    ();
		operand& destination();
	};

	template <>
	class format<format_category::shallow_move>
		: private format_base {
		argument_iterator* _M_Op_ArgIter ;
		operand*		   _M_Op_Source		,
			   *		   _M_Op_Destination;
	public:
		using string_type = std::string;
		format(instruction&);

	public:
		operand& source	    ();
		operand& destination();
	};

	template <>
	class format<format_category::deep_move>
		: private format_base {
		argument_iterator* _M_Op_ArgIter ;
		operand*		   _M_Op_Source		,
			   *		   _M_Op_Destination;
	public:
		using string_type = std::string;
		format(instruction&);

	public:
		operand& source	    ();
		operand& destination();
	};
}