#pragma once
#include <ampersand/diopter/stack.hpp>

#include <ampersand/diopter/type.hpp>
#include <ampersand/diopter/symbol.hpp>
#include <ampersand/diopter/object.hpp>

namespace ampersand::diopter {
	class scope {
		symbol _M_Symbol;
		stack  _M_Stack ;
		scope* _M_Super ;
	
	public:
		using name_type   = type::name_type;

		scope(scope&); // For Derived Scope
		scope();	   // For Super Scope

	public:
		symbol& get_scoped_symbol ();
		stack&  get_scoped_stack  ();

		type    find_scoped_symbol(name_type);
		type    find_global_symbol(name_type);

		object  find_scoped_object(name_type);
		object  find_global_object(name_type);
	};
}