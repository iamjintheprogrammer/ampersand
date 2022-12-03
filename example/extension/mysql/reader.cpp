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

	ampersand::schema::table<test_meta> Table ("testtable");
	ampersand::schema::syntax::select   Syntax( Table );

	ampersand::extension::mysql::driver				  Driver;
	ampersand::extension::mysql::connection::endpoint Endpoint  ("127.0.0.1", 6500, argv[1], argv[2]);
	ampersand::extension::mysql::connection			  Connection(Driver, Endpoint, "test");

	ampersand::extension::mysql::parser			 Parser(Syntax);
	ampersand::extension::mysql::reader			 Reader(ampersand::meta::body::raw{}, Connection, Parser);
	ampersand::extension::mysql::reader_iterator ReaderIterator(Reader);

	std::cout << (*ReaderIterator)[test {}] << std::endl;
	std::cout << (*ReaderIterator)[test2{}] << std::endl;
}