#include <ampersand/meta.hpp>

#include <iostream>
#include <chrono>

inline constexpr ampersand::meta::attribute<ampersand::meta::u32> attr_1{ "Attr1" };
inline constexpr ampersand::meta::attribute<ampersand::meta::u64> attr_2{ "Attr2" };

inline constexpr ampersand::meta::meta_type	type_1 { "Type1", attr_1, attr_2 };
using object = ampersand::meta::meta_object<std::remove_const_t<decltype(type_1)>>;

void set_value(object& pObject) {
	auto pf_begin = std::chrono::high_resolution_clock::now();

	pObject[attr_1] = 5;
	pObject[attr_2] = 3;

	auto pf_end = std::chrono::high_resolution_clock::now();

	std::cout << "Object Member Accessing Performance : "
			  << std::chrono::duration_cast<std::chrono::nanoseconds>(pf_end - pf_begin)
			  << "\n\n";
}

void get_value(object& pObject) {
	std::cout << "Value of "
			  << pObject.type_of().get_attribute(attr_1).name() << " : " << *pObject[attr_1] << "\n"
			  << "Value of "
			  << pObject.type_of().get_attribute(attr_2).name() << " : " << *pObject[attr_2] << "\n\n";
}

void copy_object(object& pObject) {
	object SampleCopy(type_1);

	auto pf_begin = std::chrono::high_resolution_clock::now();
	SampleCopy = pObject;

	auto pf_end = std::chrono::high_resolution_clock::now();

	std::cout << "Object Copy Performance : "
			  << std::chrono::duration_cast<std::chrono::nanoseconds>(pf_end - pf_begin)
			  << "\n";

	std::cout << "Value of Copied "
			  << SampleCopy.type_of().get_attribute(attr_1).name() << " : " << *SampleCopy[attr_1] << "\n"
			  << "Value of Copied "
			  << SampleCopy.type_of().get_attribute(attr_2).name() << " : " << *SampleCopy[attr_2] << "\n";
}

void performance() {
	auto pf_begin = std::chrono::high_resolution_clock::now();
	object SampleObject(type_1, "PfObject");
	auto pf_end   = std::chrono::high_resolution_clock::now();

	std::cout << "Object Creation Performance : "
			  << std::chrono::duration_cast<std::chrono::nanoseconds>(pf_end - pf_begin)
			  << "\n";
}

int main() {
	// Let's Assign Two Objects.
	object SampleObject(type_1, "Object1");
	
	std::cout << "[AMPERSAND][EXAMPLE][META_TYPE]\n"
			  << "This Sample demonstrates how to create and use meta type System of Ampersand.\n\n";

	performance();
	set_value  (SampleObject);
	get_value  (SampleObject);
	copy_object(SampleObject);
}