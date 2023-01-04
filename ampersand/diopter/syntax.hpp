#pragma once
#include <ampersand/meta.hpp>

namespace ampersand::diopter {
	class syntax_impl {
	public:
		enum class operator_category {
			add		,      add_and_store,
			subtract, subtract_and_store,
			multiply, multiply_and_store,
			divide  ,   divide_and_store,
			
			and_with, or_with,

			greater_than, greater_or_equal,
			   less_than,    less_or_equal, not_to,

			equal, not_equal,
			move , copy, reference,

			invoke,
			invoke_method,
			invoke_static_method
		};
	public:
		
	};
}