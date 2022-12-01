#include "buffer_body.hpp"

int main() {
	auto Buffer = ampersand::proto::make_buffer
		( ampersand::proto::fields::remapped_field    <std::uint32_t, std::uint64_t>,
		  ampersand::proto::fields::field		      <int>,
		  ampersand::proto::fields::send_size_field   <int>,
		  ampersand::proto::fields::receive_size_field<std::uint64_t>);
	auto Object = ampersand::meta::meta_object
					(ampersand::meta::body::raw{},
					 ampersand::meta::meta_type
						(ampersand::meta::attribute<std::uint32_t>{},
						 ampersand::meta::attribute<int>		  {},
						 ampersand::meta::attribute<int>		  {},
						 ampersand::meta::attribute<std::uint64_t>{}));

	Object[ampersand::meta::attribute<int>{}] = 5;

	example_import_packet (Buffer, Object);
	example_pseudo_receive(Buffer);
}