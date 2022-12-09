#pragma once
#include <ampersand/poly/machine/instruction.hpp>
#include <ampersand/poly/machine/format_category.hpp>

namespace ampersand::poly::machine {
	class format_base {
	protected:
		instruction& _M_Instruction;
		format_base(instruction&);
	public:
		using string_type = std::string;
		class argument_iterator {
			friend class format_base;
			instruction::__argvec::iterator _M_Iterator;
		protected:
			argument_iterator(format_base&, bool);
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

	template <typename DecoderCategory>
	class format;
}