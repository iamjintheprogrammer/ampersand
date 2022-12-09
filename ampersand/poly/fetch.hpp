#pragma once
#include <list>
#include <ampersand/poly/poly_binary.hpp>

namespace ampersand::poly {
	class fetch {
		poly_binary&						 _M_Module  ;
		poly_binary::__instruction::iterator _M_Iterator;
		
	public:
		fetch();

	public:
		machine::instruction& peek	  ();
		machine::instruction& peek_prev();
		machine::instruction& peek_next();

	public:
		void     next();
		void     prev();
		operator bool();
	};

	class fetch_line {
		poly_binary&						 _M_Module		   ;
		poly_binary::__instruction::iterator _M_ModuleIterator ;
		poly_binary::__instruction			 _M_LineInstruction;
	public:
		fetch_line();
	
	public:
		class iterator {
			friend class fetch_line;
			poly_binary::__instruction::iterator _M_Iterator;
			iterator(poly_binary::__instruction::iterator);
 		
		public:
			machine::instruction& operator*();

			iterator&			  operator++();
			iterator			  operator++(int);

			iterator&			  operator--();
			iterator			  operator--(int);

			bool				  operator==(iterator&);
			bool				  operator!=(iterator&);
		};

		bool	 parse_next ();
		iterator begin_point();
		iterator   end_point();
	};
}