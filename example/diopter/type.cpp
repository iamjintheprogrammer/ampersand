#include <iostream>
#include <ampersand/diopter.hpp>

inline ampersand::meta::attribute<ampersand::meta::i8>  attr_i8 { "Attr1" };
inline ampersand::meta::attribute<ampersand::meta::i16> attr_i16{ "Attr2" };

inline ampersand::meta::meta_type							 type_1 { "TestType", attr_i8, attr_i16 };
inline ampersand::meta::attribute<decltype(type_1)>     attr_type_1 { "Attr3", type_1 };

inline ampersand::meta::meta_type					    type_2{ "TestType2", attr_i8, attr_i16, attr_type_1 };
inline ampersand::meta::meta_object<decltype(type_1)>   object_1{ type_1, "TestObject" };
inline ampersand::meta::meta_object<decltype(type_1)>   object_2{ type_1, "TestObject" };

int main() {
	using namespace std::string_literals;
	ampersand::diopter::type   Type(type_1);
	ampersand::diopter::symbol Symbol;

	std::cout << Type.name()					<< std::endl
			  << Type["Attr1"s].operator bool() << std::endl;

	Symbol.push_symbol(type_1);	
	Symbol.push_symbol(type_2);

	std::cout << Symbol.find_symbol("TestType") .name() << std::endl;
	std::cout << Symbol.find_symbol("TestType2")["Attr3"s].name() << std::endl;
}