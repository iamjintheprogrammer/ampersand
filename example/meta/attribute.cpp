#include <ampersand/meta/condition.hpp>
#include <ampersand/meta/attribute.hpp>

#include <iostream>

using namespace ampersand::meta;

struct original_annotation   : annotation {};
struct additional_annotation : annotation {};

void example_add_annotation() {
	attribute<int, original_annotation> Attribute;
	std::cout << typeid(Attribute).name()						    << std::endl
			  << typeid(Attribute | additional_annotation{}).name() << std::endl;
}

void example_operator() {
	attribute<int, original_annotation>   Left ;
	attribute<int, additional_annotation> Right;

	std::cout << typeid(Left <  Right).name() << std::endl
			  << typeid(Left <= Right).name() << std::endl
			  << typeid(Left >  Right).name() << std::endl
			  << typeid(Left >= Right).name() << std::endl
			  << typeid(Left == Right).name() << std::endl
			  << typeid(Left != Right).name() << std::endl;
}

int main() {
	example_add_annotation();
	example_operator	  ();
}