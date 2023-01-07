#include <iostream>
#include <ampersand/diopter.hpp>

inline ampersand::meta::attribute<ampersand::meta::i8>  attr_i8 { "Attr1" };
inline ampersand::meta::attribute<ampersand::meta::i16> attr_i16{ "Attr2" };

inline ampersand::meta::meta_type					  type_1  { "TestType", attr_i8, attr_i16 };
inline ampersand::meta::meta_object<decltype(type_1)> object_1{ type_1, "TestObject" };
inline ampersand::meta::meta_object<decltype(type_1)> object_2{ type_1, "TestObject2" };

void traverse_dfs	  (ampersand::diopter::syntax&&);
void traverse_dfs_impl(ampersand::diopter::syntax::syntax_operand&&);

void traverse_dfs_impl(ampersand::diopter::syntax::syntax_operand&& pOperand) {
	switch (pOperand.get_category()) {
	case ampersand::diopter::syntax::syntax_operand::category::syntax:
		traverse_dfs(pOperand.get_syntax());
		break;

	case ampersand::diopter::syntax::syntax_operand::category::operand:
		std::cout << "Type : " << pOperand.get_operand().type_name()
				  << "Name : " << pOperand.get_operand().	  name() << std::endl;
	}
}

void traverse_dfs(ampersand::diopter::syntax&& pSyntax) {
	std::cout << "[Verb : " << (std::uint32_t)pSyntax.get_verb() << std::endl;
	for (size_t i = 0; i < pSyntax.opreand_count(); i++) {
		traverse_dfs_impl(pSyntax[i]);
	}
	std::cout << "]\n";
}

int main() {
	using namespace std::string_literals;
	auto greater_than = object_1 < object_2 == object_1 = object_2;

	ampersand::diopter::script meta_script{
		type_1  ,
		object_1,
		object_2,

		object_1 = object_2,
		(object_1 <= object_2) = object_1
	};

	auto begin_line = meta_script.start_line();
	auto end_line   = meta_script.end_line  ();

	for (; begin_line != end_line; ++begin_line) {
		traverse_dfs(std::move(*begin_line));
	}
}