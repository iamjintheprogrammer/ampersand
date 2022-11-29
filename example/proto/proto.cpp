#include <iostream>

#include <ampersand/proto/field.hpp>
#include <ampersand/proto/annotation.hpp>
#include <ampersand/proto/annotation_traits.hpp>

#include <ampersand/proto/buffer.hpp>
#include <ampersand/proto/body.hpp>

using remap_field = ampersand::proto::fields::remapped_field<int, int64_t>;
using       field = ampersand::proto::fields::field		    <int>;

int main() {
	ampersand::proto::buffer<remap_field, field> Buffer;

	std::cout << sizeof(Buffer) << std::endl;
	Buffer[field{}] = 5;
	std::cout << Buffer[field{}] << std::endl;
}