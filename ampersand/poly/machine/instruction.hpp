#pragma once
#include <string>
#include <vector>

#include <ampersand/poly/machine/operand.hpp>
#include <ampersand/poly/machine/instruction_verb.hpp>

namespace ampersand::poly::machine {
	class instruction {
	public:
		template <typename AnyType> friend class format;
									friend class format_base;

		using string_type = std::string;
		using index_type  = std::size_t;
		using size_type   = std::size_t;

		template <typename... Operands>
		instruction(instruction_verb, Operands&&...);
		instruction_verb verb();

	private:
		using __argvec = std::vector<operand>;
			  __argvec		   _M_InstOperand; // 0 for Return Operand, 1... for Input Operand
			  instruction_verb _M_InstVerb	 ;
	};

	template <typename... Operands>
	instruction::instruction
		(instruction_verb pVerb, Operands&&... pOperand)
			: _M_InstVerb(pVerb) { ((_M_InstOperand.push_back(pOperand)), ...); }

}