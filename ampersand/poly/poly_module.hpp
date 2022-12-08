#pragma once
#include <ampersand/poly/instruction.hpp>
#include <ampersand/poly/instruction_verb.hpp>

#include <ampersand/poly/declare.hpp>

#include <list>

namespace ampersand::poly {
	class poly_module	  {
		template <typename... AnyType> friend class parser	   ;
		template <typename... AnyType> friend class poly_object;
									   friend class fetch	   ;
									   friend class fetch_line ;

		using __declare = std::list<declare>;
			  __declare _M_Declare;

		using __instruction = std::list<instruction>;
			  __instruction _M_Instruction;
			  poly_module*  _M_Prev       ;
	public:
		using value_type = instruction;
		 poly_module();
		~poly_module();

	public:
		static poly_module& current();
	private:
		void push		     (declare&);
		void push_instruction(instruction&);
		void push_enter	     ();
		void push_leave      ();
	};
}