#include <iostream>
#include <ampersand/poly/poly_any.hpp>
#include <ampersand/poly/fetch.hpp>
#include <ampersand/poly/decoder.hpp>

#include <ampersand/poly/python/desc_instruction.hpp>

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
		AnyObject("TestMethod1", AnyObject, AnyObject2);
	}

	auto& Module     = ampersand::poly::poly_module::current();
	auto  LineParser = ampersand::poly::fetch_line();
	auto  Parser     = ampersand::poly::fetch();

	while (LineParser.parse_next()) {
		std::string line;
		auto Begin = LineParser.begin_point();
		auto End   = LineParser.end_point  ();

		if (Begin == End)
			continue;

		while (Begin != End) {
			auto Decoder = ampersand::poly::decoder(*Begin);
			ampersand::poly::python::invoke_describer_unit
				((*Begin).verb(), Decoder, line);
			Begin++;
		}
		if (!line.empty())
			ParsedString += line + "\n";
	}

	std::cout << ParsedString << std::endl;
}