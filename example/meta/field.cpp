#include "field.hpp"
#include <iostream>

void example_meta_constexpr() {
	static_assert
		(decltype(Field)::get_name(Field) == "Hello World",
			"Constant Evaluation Worked !!"); // Never Fired!
}

void example_meta_add_attribute() {
	constexpr ampersand::meta::push_field_attribute_t<int, decltype(Field)>
		add_value(Field);

	std::cout << typeid(decltype(add_value)).name() << std::endl;
}