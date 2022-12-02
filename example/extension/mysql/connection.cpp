#include "connection.hpp"

int main() {
	ampersand::extension::mysql::driver				  Driver;
	ampersand::extension::mysql::connection::endpoint
		Endpoint("127.0.0.1", 6500, "root", "CpPDeV2)2!");
	
	example_mysql_connect(Driver, Endpoint);
}

ampersand::extension::mysql::connection
	example_mysql_connect
		(ampersand::extension::mysql::driver&			   pDriver	,
		 ampersand::extension::mysql::connection::endpoint pEndpoint) {
	return
		ampersand::extension::mysql::connection
			(pDriver, pEndpoint, "test");
}