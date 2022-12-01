#include "connection.hpp"

using namespace ampersand::extension::mysql;

connection::connection
	(driver& pDriver, endpoint pEndpoint, string_type pSchema)
		: connection_base(pDriver, pEndpoint, pSchema)
			{  }

connection::~connection() {}