#pragma once
#include <ampersand/poly/instruction.hpp>

namespace ampersand::poly {
	class decoder_base {
	protected:
		instruction& _M_Instruction;
		decoder_base(instruction&);
	public:
		using string_type = std::string;
		class argument_iterator {
			friend class decoder_base;
			instruction::__argvec::iterator _M_Iterator;
		protected:
			argument_iterator(decoder_base&, bool);
		public:
			operand&		   operator* ();
			argument_iterator& operator++();
			argument_iterator& operator--();
			argument_iterator  operator++(int);
			argument_iterator  operator--(int);
			
			bool			   operator==(argument_iterator&);
			bool			   operator!=(argument_iterator&);
		};

		argument_iterator begin_args();
		argument_iterator   end_args();
	};

	class decoder : public decoder_base {
	public:
		using string_type = std::string;

		decoder(instruction&);
	public:
		string_type function_name ();
		operand&    return_operand();
	};
}