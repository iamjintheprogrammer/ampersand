#include <ampersand/meta.hpp>
#include <iostream>

inline ampersand::meta::attribute<ampersand::meta::i8>  attr_i8{ "Attr1" };
inline ampersand::meta::attribute<ampersand::meta::i16> attr_i16{ "Attr2" };
inline ampersand::meta::meta_type					    type_1{ "TestType", attr_i8, attr_i16 };
inline ampersand::meta::meta_object<decltype(type_1)>   object_1{ type_1, "TestObject" };
inline ampersand::meta::meta_object<decltype(type_1)>   object_2{ type_1, "TestObject" };

int main() {
	ampersand::meta::meta_script meta_script {
		object_1,
		object_2,
		object_1 = object_2,
		object_1 < object_2
	};

	std::cout << typeid(meta_script).name() << std::endl;
}