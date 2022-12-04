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
	table	  SchemaTable(SchemaMeta, std::string("testtable"), "test1", "test2");

	mysql::driver				ConnectionDriver;
	mysql::connection::endpoint ConnectionEndpoint("127.0.0.1", 6500, argv[1], argv[2]);
	mysql::connection			Connection		  (ConnectionDriver, ConnectionEndpoint, "test");

	syntax::select		   TableSelect	      (SchemaTable, SchemaMeta, (ex1_attribute > ex2_attribute));
	mysql::parser		   TableSelectParser  (std::string{}, TableSelect);
	mysql::reader		   TableReader		  (raw_body, Connection, TableSelectParser);
	mysql::reader_iterator TableReaderIterator(TableReader);

	while (TableReaderIterator != decltype(TableReaderIterator)()) {
		auto ReadValue = *TableReaderIterator;
		std::cout
			<< "Row Value => "
			<< ReadValue[ex1_attribute] << " "
			<< ReadValue[ex2_attribute] << std::endl;
		++TableReaderIterator;
	}
}