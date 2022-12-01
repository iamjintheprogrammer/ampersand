#pragma once
#include <ampersand/extension/mysql/driver.hpp>

namespace ampersand::extension::mysql {
	class connection_base {
	protected:
		class endpoint {
			friend class connection_base;
		public:
			using string_type = std::string;
			using port_type   = std::uint16_t;
			using name_type   = std::string;

		public:
			endpoint(string_type, port_type, name_type = name_type("root"), name_type = name_type("root"));
		private:
			string_type _M_Ep_Address		  ,
						_M_Ep_Account_Name	  ,
						_M_Ep_Account_PassCode;
		};
	protected:
		using __connection_type = sql::Connection*;
		using __driver_type	    = sql::Driver*;

			  __connection_type _M_Base;
			  __driver_type		_M_Base_Driver;

	protected:
		 connection_base(driver&, endpoint&, std::string&);
		~connection_base();
	};
}