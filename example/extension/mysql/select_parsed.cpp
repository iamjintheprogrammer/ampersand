#include <ampersand/schema/syntax/select.hpp>

#include <ampersand/meta/body/raw.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <ampersand/extension/mysql/parser.hpp>
#include <ampersand/extension/mysql/reader.hpp>
#include <ampersand/extension/mysql/reader_iterator.hpp>

#include <ampersand/extension/mysql/driver.hpp>
#include <ampersand/extension/mysql/connection.hpp>

#include <iostream>
#include <chrono>

using namespace ampersand::meta;
using namespace ampersand::schema;
using namespace ampersand::extension;

struct ex1_annotation : annotation {};
struct ex2_annotation : annotation {};

attribute<int, ex1_annotation> ex1_attribute;
attribute<int, ex2_annotation> ex2_attribute;

int main(int argc, char** argv) {
	meta_type SchemaMeta (ex1_attribute, ex2_attribute);
	meta_type SchemaMeta2(ex1_attribute);
	table	  SchemaTable(SchemaMeta, std::string("testtable"), "test1", "test2");

	mysql::driver				ConnectionDriver;
	mysql::connection::endpoint ConnectionEndpoint(argv[1], std::atoi(argv[2]), argv[3], argv[4]);
	mysql::connection			Connection		  (ConnectionDriver, ConnectionEndpoint, "test");

	syntax::select		   TableSelect	      (SchemaTable, SchemaMeta, (ex1_attribute < ex2_attribute));
	mysql::reader		   TableReader		  (raw_body, Connection, mysql::parser(std::string{}, TableSelect));
	std::cout << mysql::parser(std::string{}, TableSelect)() << std::endl;
	mysql::reader_iterator TableReaderIterator(TableReader);
	decltype(TableReaderIterator) End;

	while (TableReaderIterator != End) {
		auto ReadValue = *TableReaderIterator;
		std::cout
			<< "Row Value => "
			<< ReadValue[ex1_attribute] << " "
			<< ReadValue[ex2_attribute] << std::endl;
		++TableReaderIterator;
	}
}