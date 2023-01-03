#pragma once
#include <ampersand/diopter/engine/type.hpp>

namespace ampersand::diopter {
	class object {
		type&			  _M_Type;
		type::string_type _M_Name;
	public:
		using string_type = type::string_type;
		object(type&, string_type);
		
		type&		 type_of();
		string_type& name_of();
	};
}