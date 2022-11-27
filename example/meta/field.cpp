#include "field.hpp"
#include <iostream>


void meta_add_attribute() {
	constexpr ampersand::meta::push_field_attribute_t<int, decltype(Field)>
		add_value(Field);

	std::cout << typeid(decltype(add_value)).name() << std::endl;
}