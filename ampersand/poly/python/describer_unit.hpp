#pragma once
#include <ampersand/poly/fetch.hpp>
#include <ampersand/poly/machine/instruction.hpp>

#include <ampersand/poly/machine/format/call.hpp>
#include <ampersand/poly/machine/format/call_method.hpp>

#include <ampersand/poly/machine/format/move.hpp>
#include <ampersand/poly/machine/format/object.hpp>
#include <ampersand/poly/machine/format/primitive_operator.hpp>

namespace ampersand::poly::python {
	void				call   (machine::instruction&, std::string&);
	void		 call_method   (machine::instruction&, std::string&);

	void       create_object   (machine::instruction&, std::string&);
	void       delete_object   (machine::instruction&, std::string&);
	void    reference_object   (machine::instruction&, std::string&);

	void     primitive_operator(machine::instruction&, std::string&);
	void  primitive_eq_operator(machine::instruction&, std::string&);

	void		        move(machine::instruction&, std::string&);
	void		move_shallow(machine::instruction&, std::string&);
	void		   move_deep(machine::instruction&, std::string&);

	void      describer_unit(machine::instruction_verb, machine::instruction&, std::string&);
}