#include <iostream>

#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>
#include <ampersand/meta/attribute.hpp>

#include <ampersand/poly/poly_any.hpp>
#include <ampersand/poly/poly_interface.hpp>
#include <ampersand/poly/poly_object.hpp>
#include <ampersand/poly/types/primitive.hpp>

#include <ampersand/poly/fetch.hpp>
#include <ampersand/poly/poly_binary.hpp>
#include <ampersand/poly/python/describer.hpp>

using namespace std::string_literals;

using attr_1 = ampersand::meta::attribute<ampersand::poly::i8>;
using attr_2 = ampersand::meta::attribute<ampersand::poly::i16>;

using type_1 = ampersand::poly::poly_interface<ampersand::meta::meta_type<attr_1, attr_2>>;

int main() {
	std::string ParsedString;
	{
		/*ampersand::poly::any AnyObject("Any1");
		ampersand::poly::any AnyObject2("Any2");
		ampersand::poly::any AnyObject3("Any3");
		ampersand::poly::any AnyObject4("Any4");
		ampersand::poly::any AnyObject5("Any5");

		AnyObject2 = AnyObject["Test"]["Test2"]["Test3"]["Test4"];
		AnyObject2 = AnyObject + AnyObject3 + AnyObject4 + AnyObject5;
		AnyObject("TestMethod1", AnyObject, AnyObject2)
				 ("TestMethod2")
				 ("TestMethod3");*/
		ampersand::poly::i16 TestI16(3, "TestI16");
		ampersand::poly::i32 TestI32(5, "TestI32");
		ampersand::poly::i32 TestInt(5, "TestResult");

		TestInt = TestI32 + TestI16;
		type_1 Type ("TestType" , "Test1"s, "Test2"s);
		ampersand::poly::poly_object Object (Type , "TestObject");
	}

	auto& Module     = ampersand::poly::poly_binary::current();
	auto  LineParser = ampersand::poly::fetch_line();
	auto  LineParsed = ampersand::poly::python::describer<>().describe(LineParser);

	std::cout << LineParsed << std::endl;
}