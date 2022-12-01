#include <iostream>

#include "raw.hpp"

struct test1	: ampersand::meta::annotation {};
struct test2	: ampersand::meta::annotation {};
struct test3	: ampersand::meta::annotation {};

using test1_var = ampersand::meta::attribute<int, test1>;
using test2_var = ampersand::meta::attribute<int, test2>;

int main() {
	auto meta_type 
		= ampersand::meta::meta_type(test1_var{}, test2_var{});
	auto raw_object = example_raw_create(meta_type);

	std::cout << sizeof(raw_object) << std::endl;

	example_raw_set_value  (raw_object, test1_var{}, 1);
	example_raw_set_value  (raw_object, test2_var{}, 2);

	example_raw_get_value  (raw_object, test1_var{});
	example_raw_get_value  (raw_object, test2_var{});

	example_raw_get_address(raw_object, test1_var{});
	example_raw_get_address(raw_object, test2_var{});
}