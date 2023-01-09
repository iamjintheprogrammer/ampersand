#pragma once
#include <ampersand/diopter/type_function.hpp>

namespace ampersand::diopter {
	class function::argument {
		function& impl_function;
	public:
		argument(function&);
		
		class iterator : std::iterator<std::forward_iterator_tag, type> 
		{
			friend class argument;
			function&					  impl_function;
			function::args_impl::iterator impl_iterator;

			iterator(function&, function::args_impl::iterator);
		public:
			type&			 operator*();
			type::name_type& name	  ();

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
		using		 key_type = function::args_impl::key_type;

		iterator  begin	    ();
		iterator  end	    ();
		iterator  find      (key_type);
		reference operator[](key_type);
	};
}