#pragma once
#include <ampersand/diopter/type_compound.hpp>

namespace ampersand::diopter {
	class compound::attribute {
		friend class symbol  ;
		friend class compound;

		compound& impl_compound;
	public:
		attribute(compound&);
		
		class iterator : std::iterator<std::forward_iterator_tag, type> 
		{
			friend class attribute;
			compound&					   impl_compound;
			compound::table_impl::iterator impl_iterator;

			iterator(compound&, compound::table_impl::iterator);
		public:
			type&			operator* ();
			type::name_type name      ();

			iterator& operator++();
			iterator  operator++(int);

			bool	  operator==(iterator&);
			bool	  operator!=(iterator&);
		};

	public:
		using	   value_type =		  type ;
		using	    reference =	      type&;
		using const_reference = const type&;
		using	      pointer =	      type*;
		using   const_pointer = const type*;
		using		 key_type = compound::table_impl::key_type;

		iterator  begin	    ();
		iterator  end	    ();
		iterator  find      (key_type);
		reference operator[](key_type);
		
	};
}