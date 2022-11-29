#include <iostream>

#include <ampersand/proto/field.hpp>
#include <ampersand/proto/annotation.hpp>
#include <ampersand/proto/annotation_traits.hpp>

#include <ampersand/proto/buffer.hpp>
#include <ampersand/proto/body.hpp>

using	  remap_field = ampersand::proto::fields::remapped_field <int, int64_t>;
using			field = ampersand::proto::fields::field		     <int>;
using send_size_field = ampersand::proto::fields::send_size_field<uint64_t>;

template <typename BufferT>
void pseudo_receive(BufferT&& pBuffer) {
	using buffer_t = std::remove_reference_t<BufferT>;
	size_t received_size = 8;
	if constexpr (ampersand::proto::has_send_field_attribute<typename buffer_t::meta_type>::value) {
		if (received_size != pBuffer[send_size_field{}])
			std::cout << "Failed to Receive Data !!\n";
		else
			std::cout << "Successful !!\n";
	}
}

int main() {
	ampersand::proto::buffer<remap_field, field, send_size_field> Buffer;

	std::cout << sizeof(Buffer) << std::endl;
	Buffer[field{}] = 5;
	std::cout << Buffer[field{}] << std::endl;
	pseudo_receive(Buffer);
}