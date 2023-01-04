#pragma once
#include <optional>

#include <ampersand/diopter/type.hpp>
#include <ampersand/diopter/object.hpp>

namespace ampersand::diopter {
	class stack {
		std::unordered_map<type::name_type, object> _M_Stack;
	public:
		using name_type = type::name_type;
		stack();
		
		bool   push_object(object&)  ;
		bool   pop_object (name_type);
		object find_object(name_type);
	};
}