#pragma once
#include <ampersand/meta.hpp>

namespace ampersand::diopter {
	class type {
		friend class compound;
		friend class function;

		enum class category_impl { compound, primitive, function, none };
		using		   name_impl = std::string;
		
			name_impl impl_type_name;
		category_impl impl_type_category;

		type(name_impl, category_impl);
		type		   (category_impl);
	public:
		using name_type = name_impl	   ;
		using category  = category_impl;

		name_type type_name	   ();
		category  type_category();
	};
}