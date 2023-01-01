#include "describer_unit.hpp"
#include <iostream>

using namespace ampersand::poly;
void(*invoke_describer_unit_table[])(machine::instruction&, std::string&) = {
		nullptr,
		nullptr,

		& ampersand::poly::python::call		  ,
		& ampersand::poly::python::call_method,

		& ampersand::poly::python::create_object   ,
		& ampersand::poly::python::delete_object   ,
		& ampersand::poly::python::reference_object,

		& ampersand::poly::python::primitive_operator   ,
		& ampersand::poly::python::primitive_eq_operator,

		& ampersand::poly::python::primitive_operator   ,
		& ampersand::poly::python::primitive_eq_operator,

		& ampersand::poly::python::primitive_operator,
		& ampersand::poly::python::primitive_eq_operator,

		& ampersand::poly::python::primitive_operator   ,
		& ampersand::poly::python::primitive_eq_operator,

		& ampersand::poly::python::move		   ,
		& ampersand::poly::python::move_shallow,
		& ampersand::poly::python::move_deep
};

namespace ampersand::poly::python {
	void 
		call
			(machine::instruction& pInstruction, std::string& pString) {
		machine::format
			<machine::format_category::call> inst_fmt(pInstruction);
		
		pString += inst_fmt.entry_name();
		pString += "(";

		auto arg_begin = inst_fmt.argument_begin();
		auto arg_end   = inst_fmt.argument_end  ();

		if (arg_begin != arg_end) {
			for ( ; arg_begin != arg_end; ++arg_begin) {
				machine::operand& op = *arg_begin;
				switch (op.operand_category()) {
					case machine::operand::category::constant: {
						machine::operand::constant op_const("");
						op.get_operand(op_const);

						pString += op_const.get_string_value() + ",";
						break;
					}
					
					case machine::operand::category::object: {
						machine::operand::object op_object("", "");
						op.get_operand(op_object);

						pString += op_object.name() + ",";
						break;
					}
				}
			}
			pString.pop_back();
		}

		pString += ")";
	}

	void
		call_method
			(machine::instruction& pInstruction, std::string& pString) {
		machine::format
			<machine::format_category::call_method> inst_fmt   (pInstruction);
		machine::operand::object					ob_instance("", "");

		inst_fmt.instance().get_operand(ob_instance);
		pString += ob_instance.name() 
				+  "."
				+  inst_fmt.entry_name()
				+ '(';

		auto arg_begin = inst_fmt.argument_begin();
		auto arg_end   = inst_fmt.argument_end  ();

		if (arg_begin != arg_end) {
			for ( ; arg_begin != arg_end; ++arg_begin) {
				machine::operand& op = *arg_begin;
				switch (op.operand_category()) {
					case machine::operand::category::constant: {
						machine::operand::constant op_const("");
						op.get_operand(op_const);

						pString += op_const.get_string_value() + ",";
						break;
					}
					
					case machine::operand::category::object: {
						machine::operand::object op_object("", "");
						op.get_operand(op_object);

						pString += op_object.name() + ",";
						break;
					}
				}
			}
			pString.pop_back();
		}

		pString += ")";
	}

	void
		create_object
			(machine::instruction& pInstruction, std::string& pString) {
		machine::format
			<machine::format_category::create_object>
				inst_fmt   (pInstruction);

		auto arg_begin = inst_fmt.argument_begin();
		auto arg_end   = inst_fmt.argument_end();

		if(inst_fmt.primitive_category()
				!= machine::operand::primitive::category::non_primitive) {
			machine::operand::constant op_init(0);
			(*arg_begin).get_operand  (op_init);

			pString += inst_fmt.name()
					+ '='
					+ op_init.get_string_value();
			return;
		}

		pString += inst_fmt.name()
				+ "="
				+ inst_fmt.type_name()
				+ '(';

		if (arg_begin != arg_end) {
			for ( ; arg_begin != arg_end; ++arg_begin) {
				machine::operand& op = *arg_begin;
				switch (op.operand_category()) {
					case machine::operand::category::constant: {
						machine::operand::constant op_const("");
						op.get_operand(op_const);

						pString += op_const.get_string_value() + ",";
						break;
					}
					
					case machine::operand::category::object: {
						machine::operand::object op_object("", "");
						op.get_operand(op_object);

						pString += op_object.name() + ",";
						break;
					}
				}
			}
			pString.pop_back();
		}

		pString += ")";
	}
	
	void delete_object(machine::instruction&, std::string&) {}
	void
		reference_object
			(machine::instruction& pInstruction, std::string& pString) {
		machine::format<machine::format_category::reference_object>
			inst_ref(pInstruction);
		
		pString += inst_ref.name() + '[';
		switch (inst_ref.key().operand_category()) {
			case machine::operand::category::object: {
				machine::operand::object   op_object("", "");
				inst_ref.key().get_operand(op_object);

				pString += op_object.name() + ']';
				return;
			}

			case machine::operand::category::constant: {
				machine::operand::constant op_constant("");
				inst_ref.key().get_operand(op_constant);

				pString += op_constant.get_string_value() + ']';
				return;
			}
		}
	}

	void
		primitive_operator
			(machine::instruction& pInstruction, std::string& pString) {
		machine::format<machine::format_category::primitive_operator>
			inst_primitive(pInstruction);

		switch (inst_primitive.left().operand_category()) {
			case machine::operand::category::object: {
				machine::operand::object		  op_left("", "");
				inst_primitive.left().get_operand(op_left);

				pString += op_left.name();
				break;
			}
			case machine::operand::category::constant: {
				machine::operand::constant	      op_left("");
				inst_primitive.left().get_operand(op_left);

				pString += op_left.get_string_value();
				break;
			}
		}

		switch (pInstruction.verb()) {
			case machine::instruction_verb::op_add:
				pString += '+';
				break;
			case machine::instruction_verb::op_sub:
				pString += '-';
				break;
			case machine::instruction_verb::op_mul:
				pString += '*';
				break;
			case machine::instruction_verb::op_div:
				pString += '/';
				break;

		}

		switch (inst_primitive.right().operand_category()) {
			case machine::operand::category::object: {
				machine::operand::object		   op_right("", "");
				inst_primitive.right().get_operand(op_right);

				pString += op_right.name();
				break;
			}
			case machine::operand::category::constant: {
				machine::operand::constant	       op_right("");
				inst_primitive.right().get_operand(op_right);

				pString += op_right.get_string_value();
				break;
			}
		}
		
	}
	void
		primitive_eq_operator
			(machine::instruction& pInstruction, std::string& pString) {
		machine::format<machine::format_category::primitive_operator>
			inst_primitive(pInstruction);
		
		machine::operand::object		  op_object("", "");
		if (!inst_primitive.left().get_operand(op_object))
			return;

		std::string str_line(op_object.name());
		switch (pInstruction.verb()) {
			case machine::instruction_verb::op_addeq:
				str_line += "+=";
				break;
			case machine::instruction_verb::op_subeq:
				str_line += "-=";
				break;
			case machine::instruction_verb::op_muleq:
				str_line += "*=";
				break;
			case machine::instruction_verb::op_diveq:
				str_line += "/=";
				break;
		}

		pString = str_line + '(' + pString + ')';
	}

	void
		move
			(machine::instruction& pInstruction, std::string& pString) {
		machine::format
			<machine::format_category::move> inst_move(pInstruction);

		machine::operand::object			ob_dst("", "");
		inst_move.destination().get_operand(ob_dst);

		pString = ob_dst.name() + '=' + pString;
	}

	void
		move_shallow
			(machine::instruction& pInstruction, std::string& pString) {
		machine::format
			<machine::format_category::deep_move> inst_move(pInstruction);

		machine::operand::object			ob_dst("", "");
		inst_move.destination().get_operand(ob_dst);

		pString = ob_dst.name() + '=' + pString;
	}

	void 
		move_deep
			(machine::instruction& pInstruction, std::string& pString) {
		machine::format
			<machine::format_category::deep_move> inst_move(pInstruction);

		machine::operand::object			ob_dst("", "");
		inst_move.destination().get_operand(ob_dst);

		pString = ob_dst.name() + '=' + pString;
	}

	void
		describer_unit
			(machine::instruction_verb pVerb   ,
			 machine::instruction&	   pDecoder,
			 std::string&			   pString) {
		invoke_describer_unit_table[(std::uint32_t)pVerb]
			(pDecoder, pString);
	}
}