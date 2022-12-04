#include <ampersand/schema/table.hpp>
#include <iostream>

using namespace ampersand::meta;
using namespace ampersand::schema;

struct ex1_annotation : annotation {};
struct ex2_annotation : annotation {};
struct ex3_annotation : annotation {};

using  ex1_attribute  = attribute<int		   , ex1_annotation>;
using  ex2_attribute  = attribute<std::uint64_t, ex2_annotation>;
using  ex3_attribute  = attribute<float		   , ex3_annotation>;

void example_table() {
	meta_type MetaTable { ex1_attribute{}, ex2_attribute{}, ex3_attribute{} };
	table         Table { MetaTable, std::string("Table"), "slot1", "slot2", "slot3"};

	std::cout
		<< Table[ex1_attribute{}] << std::endl
		<< Table[ex2_attribute{}] << std::endl
		<< Table[ex3_attribute{}] << std::endl;
}

int main() {
	example_table();
}