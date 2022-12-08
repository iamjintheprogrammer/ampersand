#pragma once
#include <list>
#include <ampersand/poly/poly_module.hpp>

namespace ampersand::poly {
	class fetch {
		poly_module&						 _M_Module  ;
		poly_module::__instruction::iterator _M_Iterator;
		
	public:
		fetch();

	public:
		instruction& peek	  ();
		instruction& peek_prev();
		instruction& peek_next();

	public:
		void     next();
		void     prev();
		operator bool();
	};

	class fetch_line {
		poly_module&						 _M_Module		   ;
		poly_module::__instruction::iterator _M_ModuleIterator ;
		poly_module::__instruction			 _M_LineInstruction;
	public:
		fetch_line();
	
	public:
		class iterator {
			friend class fetch_line;
			poly_module::__instruction::iterator _M_Iterator;
			iterator(poly_module::__instruction::iterator);
 		
		public:
			instruction& operator*();

			iterator&	 operator++();
			iterator     operator++(int);

			iterator&    operator--();
			iterator     operator--(int);

			bool	     operator==(iterator&);
			bool	     operator!=(iterator&);
		};

		bool	 parse_next ();
		iterator begin_point();
		iterator   end_point();
	};
}