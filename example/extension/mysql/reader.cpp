#include <ampersand/extension/mysql/connection.hpp>
#include <ampersand/extension/mysql/driver.hpp>

#include <ampersand/extension/mysql/parser.hpp>
#include <ampersand/extension/mysql/reader.hpp>
#include <ampersand/extension/mysql/reader_iterator.hpp>

#include <ampersand/schema/row.hpp>
#include <ampersand/schema/field.hpp>
#include <ampersand/schema/table.hpp>
#include <ampersand/schema/select.hpp>
#include <ampersand/schema/type.hpp>

#include <ampersand/meta/body/raw.hpp>

#include <iostream>

struct test_annotation  : ampersand::meta::annotation {};
struct test2_annotation : ampersand::meta::annotation {};

using test  = ampersand::meta::attribute<int, test_annotation> ;
using test2 = ampersand::meta::attribute<int, test2_annotation>;

using test_meta = ampersand::meta::meta_type<test, test2>;

int main(int argc, char** argv) {
	if (argc < 3) {
		std::cout << "Not Enough Parameter.\n";
		return 1;
	}

	ampersand::schema::field Field1{ test {} };
	ampersand::schema::field Field2{ test2{} };

	ampersand::schema::table<test_meta> Table ("testtable");
	ampersand::schema::row				Row   { Field1, Field2 };

	ampersand::schema::syntax::select   Select( Table, Row, (Field1 < Field2) || (Field1 == Field2));
	ampersand::schema::syntax::insert   Insert(Table);

	Table[test{}] = "test";
	Table[test2{}] = "test2";

	Insert[test{}]  = 3;
	Insert[test2{}] = 4;

	ampersand::extension::mysql::driver				  Driver;
	ampersand::extension::mysql::connection::endpoint Endpoint  ("127.0.0.1", 6500, argv[1], argv[2]);
	ampersand::extension::mysql::connection			  Connection(Driver, Endpoint, "test");

	ampersand::extension::mysql::parser ParserInsert (Insert);
	ampersand::extension::mysql::parser ParserSselect(Select);
	std::cout << ParserInsert () << std::endl;
	std::cout << ParserSselect() << std::endl;
}