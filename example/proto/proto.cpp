#include <iostream>

#include <ampersand/proto/field.hpp>
#include <ampersand/proto/annotation.hpp>
#include <ampersand/proto/annotation_traits.hpp>

#include <ampersand/proto/buffer.hpp>
#include <ampersand/proto/body.hpp>

template <typename BufferT>
void pseudo_receive(BufferT&& pBuffer) {
	using buffer_t = std::remove_const_t<std::remove_reference_t<BufferT>>;
	using namespace ampersand::proto;
	using namespace ampersand::meta::utility;

	if (has_annotated_attribute<buffer_t, is_remapped>::value)
		std::cout << "Have Field\n";

	std::cout << pBuffer[ampersand::proto::fields::field<int>] << std::endl;
}

int main() {
	auto Buffer = ampersand::proto::make_buffer
		( ampersand::proto::fields::remapped_field    <std::uint32_t, std::uint64_t>,
		  ampersand::proto::fields::field		      <int>,
		  ampersand::proto::fields::send_size_field   <int>,
		  ampersand::proto::fields::receive_size_field<std::uint64_t>);

	Buffer[ampersand::proto::fields::field<int>] = 5;

	pseudo_receive(Buffer);
	std::cout << sizeof(Buffer) << std::endl;
}