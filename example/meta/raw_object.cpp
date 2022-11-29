#include <ampersand/meta/body/raw.hpp>
#include <ampersand/meta/meta_object.hpp>
#include <iostream>

struct test1	: ampersand::meta::annotation {};
struct test2	: ampersand::meta::annotation {};

using test1_var = ampersand::meta::attribute<int, test1>;
using test2_var = ampersand::meta::attribute<int, test2>;

int main() {
	auto meta = ampersand::meta::make_meta_type(test1_var{}, test2_var{});
	ampersand::meta::meta_object<ampersand::meta::body::raw, decltype(meta)> Object;
}