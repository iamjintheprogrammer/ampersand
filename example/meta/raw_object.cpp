#include <ampersand/meta/object.hpp>
#include <iostream>

struct test1	: ampersand::meta::annotation {};
struct test2	: ampersand::meta::annotation {};

using test1_var = ampersand::meta::attribute<int, test1>;
using test2_var = ampersand::meta::attribute<int, test2>;

int main() {
	auto meta = ampersand::meta::make_meta_type(test1_var{}, test2_var{});
	ampersand::meta::raw_object<decltype(meta)> Object;
}