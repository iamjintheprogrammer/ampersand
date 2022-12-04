#include <ampersand/schema/syntax/select.hpp>

#include <ampersand/meta/body/raw.hpp>
#include <ampersand/meta/body/tuple.hpp>
#include <ampersand/meta/body/tag.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <iostream>

using namespace ampersand::meta;
using namespace ampersand::schema;

struct ex1_annotation : annotation {};
struct ex2_annotation : annotation {};
struct ex3_annotation : annotation {};

attribute<int, ex1_annotation> ex1_attribute;
attribute<int, ex2_annotation> ex2_attribute;
attribute<int, ex3_annotation> ex3_attribute;

int main() {
	meta_type SchemaMeta (ex1_attribute, ex2_attribute, ex3_attribute);
	table	  SchemaTable(SchemaMeta, std::string("TestTable"), "test1", "test2", "test3");

	std::cout
		<< SchemaTable[ex1_attribute] << std::endl
		<< SchemaTable[ex2_attribute] << std::endl
		<< SchemaTable[ex3_attribute] << std::endl;

	syntax::select TableSelect(SchemaTable, SchemaMeta, (ex1_attribute <= ex2_attribute));

}