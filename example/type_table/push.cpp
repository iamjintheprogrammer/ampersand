#include <type_table/all.hpp>
#include <iostream>

void example_push_front() {
	std::cout << std::boolalpha
			  << std::is_same_v
					<ampersand::type_table::type_table  <int, float>,
					 ampersand::type_table::push_front_t<int, ampersand::type_table::type_table<float>>>
			  << std::endl;
}

void example_push_back() {
	std::cout << std::boolalpha
			  << std::is_same_v
					<ampersand::type_table::type_table <int, float>,
					 ampersand::type_table::push_back_t<float, ampersand::type_table::type_table<int>>>
			  << std::endl;
}