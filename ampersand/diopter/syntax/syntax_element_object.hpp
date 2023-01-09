#pragma once
#include <ampersand/diopter/syntax/syntax_element.hpp>

namespace ampersand::diopter::syntax {
	class object : public element {
		using name_type_impl = std::string;
		meta::primitive_category impl_type_primitive;
		name_type_impl			 impl_type,
								 impl_name;
	public:
		using  name_type = name_type_impl;
		object(name_type, name_type);
		object(name_type, meta::primitive_category);

		name_type&					  name	   ();
		name_type&				 type_name	   ();
		meta::primitive_category type_primitive();
	};
}