#include <iostream>
#include <ampersand/poly/poly_any.hpp>
#include <ampersand/poly/fetch.hpp>
#include <ampersand/poly/poly_binary.hpp>
#include <ampersand/poly/python/describer.hpp>

int main() {
	std::string ParsedString;
	{
		ampersand::poly::any AnyObject ("Any1");
		ampersand::poly::any AnyObject2("Any2");
		ampersand::poly::any AnyObject3("Any3");
		ampersand::poly::any AnyObject4("Any4");
		ampersand::poly::any AnyObject5("Any5");

		AnyObject2 = AnyObject["Test"]["Test2"]["Test3"]["Test4"];
		AnyObject2 = AnyObject + AnyObject3 + AnyObject4 + AnyObject5;
		AnyObject("TestMethod1", AnyObject, AnyObject2)
				 ("TestMethod2")
				 ("TestMethod3");
	}

	auto& Module     = ampersand::poly::poly_binary::current();
	auto  LineParser = ampersand::poly::fetch_line();
	auto  LineParsed = ampersand::poly::python::describer<>().describe(LineParser);

	std::cout << LineParsed << std::endl;
}