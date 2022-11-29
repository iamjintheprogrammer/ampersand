#include <ampersand/meta/body/raw.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <iostream>

struct test1	: ampersand::meta::annotation {};
struct test2	: ampersand::meta::annotation {};
struct test3	: ampersand::meta::annotation {};

using test1_var = ampersand::meta::attribute<int, test1>;
using test2_var = ampersand::meta::attribute<int, test2>;

void test() {
	std::cout << "hello\n";
}

int main() {
	using namespace ampersand::meta;

	meta_type   Meta	   { test1_var{}, test2_var{} };
	meta_object MetaObject ( body::raw{}, Meta );
}