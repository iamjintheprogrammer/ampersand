#pragma once
#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_error.h>

#include <jdbc/cppconn/connection.h>
#include <jdbc/cppconn/datatype.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>

namespace ampersand::extension::mysql {
	class driver {
		void* _M_Base;
		friend class connection;
		friend class connection_base;
	public:
		driver ();
	};
}