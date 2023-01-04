#pragma once
#include <ampersand/diopter/symbol.hpp>
#include <ampersand/diopter/type.hpp>

namespace ampersand::diopter {
	class object {
		type			_M_Type;
		type::name_type _M_Name;
	public:
		using  name_type = type::name_type;
		 object(name_type, type&);
		~object();

		type	  type_of();
		name_type name	 ();
	};

	class constant {
		type			_M_Type;
		type::name_type _M_Name;
	public:
		using  name_type = type::name_type;
		 constant(name_type, type&);
		~constant();

		type	  type_of();
		name_type name	 ();
	};
}