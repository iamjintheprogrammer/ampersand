#include <ampersand/meta.hpp>
#include <iostream>

inline ampersand::meta::attribute<ampersand::meta::i8>  attr_i8  { "Attr1" };
inline ampersand::meta::attribute<ampersand::meta::i16> attr_i16 { "Attr2" };
inline ampersand::meta::meta_type					    type_1   { "TestType", attr_i8, attr_i16 };
inline ampersand::meta::meta_object<decltype(type_1)>   object_1 { type_1, "TestObject" };
inline ampersand::meta::meta_object<decltype(type_1)>   object_2 { type_1, "TestObject" };

int main() {
	std::cout
		<< "Single Operation Types\n\n"
		<< typeid(object_1 <  object_2)			  .name() << std::endl
		<< typeid(object_1 <= object_2)			  .name() << std::endl
		<< typeid(object_1 >  object_2)			  .name() << std::endl
		<< typeid(object_1 >= object_2)			  .name() << std::endl
		<< typeid(object_1 == object_2)			  .name() << std::endl
		<< typeid(object_1 != object_2)			  .name() << std::endl
		<< typeid(object_1 +  object_2)			  .name() << std::endl
		<< typeid(object_1 += object_2)			  .name() << std::endl
		<< typeid(object_1 -  object_2)			  .name() << std::endl
		<< typeid(object_1 -= object_2)			  .name() << std::endl
		<< typeid(object_1 *  object_2)			  .name() << std::endl
		<< typeid(object_1 *= object_2)			  .name() << std::endl
		<< typeid(object_1 /  object_2)			  .name() << std::endl
		<< typeid(object_1 /= object_2)			  .name() << std::endl
		<< typeid(object_1  = std::move(object_2)).name() << std::endl << std::endl;

	std::cout
		<< "Multiple Operation Types\n\n"
		<< typeid((object_1 < object_2) <  object_1)		   .name() << std::endl
		<< typeid((object_1 < object_2) <= object_1)		   .name() << std::endl
		<< typeid((object_1 < object_2) >  object_1)		   .name() << std::endl
		<< typeid((object_1 < object_2) >= object_1)		   .name() << std::endl
		<< typeid((object_1 < object_2) == object_1)		   .name() << std::endl
		<< typeid((object_1 < object_2) != object_1)		   .name() << std::endl
		<< typeid((object_1 < object_2)  = object_1)		   .name() << std::endl
		<< typeid((object_1 < object_2)  = std::move(object_1)).name() << std::endl << std::endl;

	std::cout
		<< "Literal Operation Types\n\n"
		<< typeid(object_1 <  7).name() << std::endl
		<< typeid(object_1 <= 7).name() << std::endl
		<< typeid(object_1 >  7).name() << std::endl
		<< typeid(object_1 >= 7).name() << std::endl
		<< typeid(object_1 == 7).name() << std::endl
		<< typeid(object_1 != 7).name() << std::endl
		<< typeid(object_1 +  7).name() << std::endl
		<< typeid(object_1 += 7).name() << std::endl
		<< typeid(object_1 -  7).name() << std::endl
		<< typeid(object_1 -= 7).name() << std::endl
		<< typeid(object_1 *  7).name() << std::endl
		<< typeid(object_1 *= 7).name() << std::endl
		<< typeid(object_1 /  7).name() << std::endl
		<< typeid(object_1 /= 7).name() << std::endl << std::endl;
}