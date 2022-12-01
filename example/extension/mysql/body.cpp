#include <ampersand/extension/mysql/body.hpp>
#include <ampersand/extension/mysql/table.hpp>

#include <ampersand/extension/mysql/types.hpp>
#include <ampersand/extension/mysql/types_annotation.hpp>

#include <ampersand/meta/meta.hpp>
#include <iostream>

int main() {
	using namespace std::string_literals;
	using namespace ampersand;
	using namespace ampersand::extension::mysql;
	using namespace ampersand::meta;

	meta_type 
		MetaType
			{big_int<extension::mysql::annotation::not_null>,
			 varchar<20, extension::mysql::annotation::not_null>};

	auto Table = ampersand::extension::mysql::make_table(MetaType, "Hello"s, "Hello2"s);
	Table[big_int<extension::mysql::annotation::not_null>] = 5;
	std::cout << Table[big_int<extension::mysql::annotation::not_null>] << std::endl;
}