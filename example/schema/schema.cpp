#include <ampersand/schema/row.hpp>
#include <ampersand/schema/field.hpp>
#include <ampersand/schema/table.hpp>
#include <ampersand/schema/select.hpp>
#include <ampersand/schema/type.hpp>

#include <ampersand/extension/mysql/parser.hpp>

#include <iostream>

using test  = ampersand::meta::attribute<int>;
using test2 = ampersand::meta::attribute<float>;

using test_meta = ampersand::meta::meta_type<test, test2>;

int main() {
	ampersand::schema::field Field { test {} };
	ampersand::schema::field Field2{ test2{} };

	ampersand::schema::table<test_meta> Table  ("TestTable", "test1", "test2");
	ampersand::schema::row				Row
		(ampersand::meta::body::tuple {},
			Field,
			Field2
		);
	ampersand::schema::syntax::select Syntax ( Table, Row );

	std::cout 
		<< ampersand::extension::mysql::parser(Syntax)() 
		<< std::endl;
}