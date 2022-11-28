#include <ampersand/proto/proto.hpp>
#include <iostream>

int main() {
	ampersand::proto::buffer 
		Buffer
			{ ampersand::meta::make_meta_type
				(ampersand::proto::sent_size	<>,
				 ampersand::proto::received_size<>,
				 ampersand::proto::field		<>)};

	std::cout << ampersand::proto::buffer_size_v<decltype(Buffer)::meta_type> << std::endl;
	std::cout << &Buffer													  << std::endl
			  << &Buffer[ampersand::proto::sent_size    <>]					  << std::endl
			  << &Buffer[ampersand::proto::received_size<>]					  << std::endl;
}