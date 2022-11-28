#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/object.hpp>
#include <ampersand/meta/implement.hpp>

#include <iostream>

struct test1 : ampersand::meta::annotation {};
struct test2 : ampersand::meta::annotation {};

using test1_var = ampersand::meta::attribute<int, ampersand::meta::annotation_set<test1>>;
using test2_var = ampersand::meta::attribute<int, ampersand::meta::annotation_set<test2>>;

int main() {
	auto meta = ampersand::meta::make_meta_type(test1_var{}, test2_var{});

	ampersand::meta::object <decltype(meta)> Object;
	ampersand::meta::method < [](ampersand::meta::object <decltype(meta)>& pObj) { std::cout << "Hello World\n"; }, ampersand::meta::annotation_set<>> Method;

	Object[test1_var{}] = 5;
	ampersand::meta::implementation<decltype(Object), ampersand::meta::traits<decltype(Method)>> Impl(Object);
	Impl(Method);
	
	std::cout << Object[test1_var{}] << std::endl;
}