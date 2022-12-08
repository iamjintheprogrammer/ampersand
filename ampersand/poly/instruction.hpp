#pragma once
#include <string>
#include <vector>

#include <ampersand/poly/operand.hpp>
#include <ampersand/poly/instruction_verb.hpp>

namespace ampersand::poly {
	class instruction	  {
	public:
		friend class decoder;
		friend class decoder_base;

		using string_type = std::string;
		using index_type  = std::size_t;
		using size_type   = std::size_t;

		template <typename... Operands>
		instruction(instruction_verb, string_type, Operands&&...);
		instruction_verb verb();

	private:
		using __argvec = std::vector<operand>;
			  __argvec		   _M_InstOperand; // 0 for Return Operand, 1... for Input Operand
			  string_type	   _M_InstName   ;
			  instruction_verb _M_InstVerb	 ;
	};

	template <typename... Operands>
	instruction::instruction
		(instruction_verb pVerb,
			string_type pName, Operands&&... pOperand)
				: _M_InstVerb(pVerb)  ,
				  _M_InstName(pName)  { ((_M_InstOperand.push_back(pOperand)), ...); }

}