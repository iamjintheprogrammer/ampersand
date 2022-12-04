#include <iostream>
#include <chrono>

#include <ampersand/meta/body/raw.hpp>
#include <ampersand/meta/body/tuple.hpp>
#include <ampersand/meta/body/tag.hpp>
#include <ampersand/meta/meta_object.hpp>

using namespace ampersand::meta;

struct ex1_annotation : annotation {};
struct ex2_annotation : annotation {};
struct ex3_annotation : annotation {};

using  ex1_attribute = attribute<int		  , ex1_annotation>;
using  ex2_attribute = attribute<std::uint64_t, ex2_annotation>;
using  ex3_attribute = attribute<float		  , ex3_annotation>;

void example_raw_body() {
	meta_type   ex_meta_type   { ex1_attribute{}, ex2_attribute{}, ex3_attribute{} };
	meta_object ex_meta_object { raw_body, ex_meta_type };

	std::cout
		<< typeid(ex_meta_type)  .name() << std::endl
		<< typeid(ex_meta_object).name() << "\n\n";

	auto pf_begin = std::chrono::high_resolution_clock::now();
	ex_meta_object[ex1_attribute{}] = 5;
	ex_meta_object[ex2_attribute{}] = 6;
	ex_meta_object[ex3_attribute{}] = 5.5;
	auto pf_end   = std::chrono::high_resolution_clock::now();

	std::cout
		<< ex_meta_object[ex1_attribute{}] << std::endl
		<< ex_meta_object[ex2_attribute{}] << std::endl
		<< ex_meta_object[ex3_attribute{}] << "\n\n";

	std::cout << "Fetch / Modify Performance : "
			  << (pf_end - pf_begin).count() << std::endl;
}

void example_tuple_body() {
	meta_type   ex_meta_type   { ex1_attribute{}, ex2_attribute{}, ex3_attribute{} };
	meta_object ex_meta_object { tuple_body, ex_meta_type };

	std::cout
		<< typeid(ex_meta_type)  .name() << std::endl
		<< typeid(ex_meta_object).name() << "\n\n";

	auto pf_begin = std::chrono::high_resolution_clock::now();
	ex_meta_object[ex1_attribute{}] = 5;
	ex_meta_object[ex2_attribute{}] = 6;
	ex_meta_object[ex3_attribute{}] = 5.5;
	auto pf_end   = std::chrono::high_resolution_clock::now();

	std::cout
		<< ex_meta_object[ex1_attribute{}] << std::endl
		<< ex_meta_object[ex2_attribute{}] << std::endl
		<< ex_meta_object[ex3_attribute{}] << "\n\n";

	std::cout << "Fetch / Modify Performance : "
			  << (pf_end - pf_begin).count() << std::endl;
}

void example_tag_body() {
	meta_type   ex_meta_type   { ex1_attribute{}, ex2_attribute{}, ex3_attribute{} };
	meta_object ex_meta_object { tag_body<std::string>, ex_meta_type };

	std::cout
		<< typeid(ex_meta_type)  .name() << std::endl
		<< typeid(ex_meta_object).name() << "\n\n";

	auto pf_begin = std::chrono::high_resolution_clock::now();
	ex_meta_object[ex1_attribute{}] = 5;
	ex_meta_object[ex2_attribute{}] = 6;
	ex_meta_object[ex3_attribute{}] = 5.5;
	auto pf_end   = std::chrono::high_resolution_clock::now();

	ex_meta_object.key_of(ex1_attribute{}) = "example1";
	ex_meta_object.key_of(ex2_attribute{}) = "example2";
	ex_meta_object.key_of(ex3_attribute{}) = "example3";

	std::cout
		<< ex_meta_object[ex1_attribute{}] << std::endl
		<< ex_meta_object[ex2_attribute{}] << std::endl
		<< ex_meta_object[ex3_attribute{}] << "\n\n";

	std::cout
		<< ex_meta_object.key_of(ex1_attribute{}) << std::endl
		<< ex_meta_object.key_of(ex2_attribute{}) << std::endl
		<< ex_meta_object.key_of(ex3_attribute{}) << std::endl;

	std::cout << "Fetch / Modify Performance : "
			  << (pf_end - pf_begin).count() << std::endl;
}

int main() {
	example_raw_body  ();
	example_tuple_body();
	example_tag_body  ();
}