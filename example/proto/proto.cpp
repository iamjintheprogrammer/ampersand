#include <iostream>

#include <ampersand/proto/field.hpp>
#include <ampersand/proto/annotation.hpp>
#include <ampersand/proto/annotation_traits.hpp>

#include <ampersand/proto/buffer.hpp>
#include <ampersand/proto/body.hpp>

using	  remap_field = ampersand::proto::fields::remapped_field <int, int64_t>;
using			field = ampersand::proto::fields::field		     <int>;
using send_size_field = ampersand::proto::fields::send_size_field<uint64_t>;

int main() {
	ampersand::proto::buffer<remap_field, field, send_size_field> Buffer;
	std::cout 
		<< ampersand::proto::has_annotation
				<remap_field,
				 ampersand::proto::is_field>::value 
		<< std::endl;
}