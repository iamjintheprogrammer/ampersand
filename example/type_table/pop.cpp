#include "pop.hpp"

void example_pop_front() {
	std::cout
		<< std::boolalpha
		<< std::is_same_v
				<ampersand::type_table::type_table <int, float>,
				 ampersand::type_table::pop_front_t<ampersand::type_table::type_table<double, int, float>>>
		<< std::endl;
}

void example_pop_back() {
	std::cout
		<< std::boolalpha
		<< std::is_same_v
				<ampersand::type_table::type_table<int, float>,
				 ampersand::type_table::pop_back<ampersand::type_table::type_table<int, float, double>>::type>
		<< std::endl;
}