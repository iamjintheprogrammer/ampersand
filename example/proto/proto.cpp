#include <ampersand/proto/proto.hpp>
#include <iostream>

int main() {
	ampersand::proto::buffer 
		Buffer
			{ ampersand::meta::make_meta_type
				(ampersand::proto::sent_size	<>,
				 ampersand::proto::received_size<>)};
	std::cout << &Buffer															<< std::endl
			  << &Buffer[ampersand::proto::sent_size    <>] << std::endl
			  << &Buffer[ampersand::proto::received_size<>] << std::endl;
}