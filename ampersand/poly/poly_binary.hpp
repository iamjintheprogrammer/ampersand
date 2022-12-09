#pragma once
#include <ampersand/poly/machine/instruction.hpp>
#include <ampersand/poly/machine/instruction_verb.hpp>

#include <ampersand/poly/declare.hpp>

#include <list>

namespace ampersand::poly {
	class poly_binary	  {
		template <typename... AnyType> friend class poly_object;
									   friend class fetch	   ;
									   friend class fetch_line ;

		using __declare = std::list<declare>;
			  __declare _M_Declare;

		using __instruction = std::list<machine::instruction>;
			  __instruction _M_Instruction;
			  poly_binary*  _M_Prev       ;
	public:
		using value_type = machine::instruction;
		 poly_binary();
		~poly_binary();

	public:
		static poly_binary& current();
	private:
		void push_declare    (declare&);
		void push_instruction(machine::instruction&);
		
		template <typename ReturnType, typename... Operand>
		void push_call		 (const char*, ReturnType&&, Operand&&...);
		template <typename ReturnType, typename... Operand>
		void push_call_method(const char*, machine::operand&, ReturnType&&, Operand&&...);

		template <typename... Operand>
		void push_object_create   (machine::operand&, Operand&&...);
		void push_object_delete	  (machine::operand&);
		void push_object_reference(machine::operand&, machine::operand&, machine::operand&);

		void push_primitive_operator(machine::instruction_verb, machine::operand&, machine::operand&, machine::operand&);
		void push_move				(machine::operand&, machine::operand&);
		void push_shallow_move	    (machine::operand&, machine::operand&);
		void push_deep_move			(machine::operand&, machine::operand&);


		void push_enter	     ();
		void push_leave      ();
	};


	template <typename ReturnType, typename... Operand>
	void 
		poly_binary::push_call
			(const char*  pEntry ,
			 ReturnType&& pReturn,
			 Operand&&... pArguments) {
		_M_Instruction.push_back
			(machine::instruction
				(machine::instruction_verb::call,
					machine::operand(pEntry), pReturn, pArguments...));
	}

	template <typename ReturnType, typename... Operand>
	void
		poly_binary::push_call_method
			(const char*	   pEntry    ,
			 machine::operand& pInstance ,
			 ReturnType&&	   pReturn   ,
			 Operand&&...	   pArguments) {
		_M_Instruction.push_back
			(machine::instruction
				(machine::instruction_verb::call_method,
					machine::operand(pEntry), pReturn, pInstance, pArguments...));
	}

	template <typename... Operand>
	void
		poly_binary::push_object_create
			(machine::operand& pInstance,
			 Operand&&...	   pArgument) {
		_M_Instruction.push_back
			(machine::instruction
				(machine::instruction_verb::ob_create, pInstance, pArgument...));
	}
}