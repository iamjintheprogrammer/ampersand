#include <ampersand/extension/json/reader.hpp>
#include <ampersand/meta/body/raw.hpp>

#include <iostream>
#include <filesystem>

struct test1_annot : ampersand::meta::annotation {};
struct test2_annot : ampersand::meta::annotation {};
struct test3_annot : ampersand::meta::annotation {};

inline constexpr ampersand::meta::attribute<int, test1_annot> test1;
inline constexpr ampersand::meta::attribute<int, test2_annot> test2;
inline constexpr ampersand::meta::attribute<int, test3_annot> test3;

template <typename T, std::size_t N>
void hex_view(T(&serialized)[N]) {
	for (int i = 0; i < N; i++) {
		if (i % 16 == 0 && i != 0)
			std::cout << std::endl;
		std::cout << std::hex << (std::uint32_t)serialized[i] << " ";
	}
}

int main() {
	ampersand::meta::meta_type   MetaType   { test1, test2, test3 };
	ampersand::meta::meta_object MetaObject { ampersand::meta::body::raw{}, MetaType };

	ampersand::extension::json::reader Reader("test.json");
	if (!Reader.read_from(MetaObject)) {
		std::cout << "Failed to Read !!\n";
	}

	std::cout << MetaObject[test1] << std::endl
			  << MetaObject[test2] << std::endl
			  << MetaObject[test3] << std::endl;

	hex_view(MetaObject.attribute_field());
}