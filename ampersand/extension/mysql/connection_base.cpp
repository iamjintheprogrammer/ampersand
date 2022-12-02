#include "connection_base.hpp"
#include <iostream>

using namespace ampersand::extension::mysql;

connection_base::endpoint::endpoint
	(string_type pAddr			 ,
	 port_type	 pPort			 ,
	 name_type   pAccountName	 , 
	 name_type   pAccountPasscode)
		: _M_Ep_Address			(pAddr)			  ,
		  _M_Ep_Account_Name	(pAccountName)	  ,
		  _M_Ep_Account_PassCode(pAccountPasscode){ 
	_M_Ep_Address += ":" + std::to_string(pPort);
}

connection_base::connection_base
	(driver& pDriver, endpoint& pEndpoint, std::string& pSchema)
		: _M_Base_Driver((__driver_type)pDriver._M_Base) {
	try {
		_M_Base
			= _M_Base_Driver->connect
					(pEndpoint._M_Ep_Address.c_str(),
					 pEndpoint._M_Ep_Account_Name   ,
					 pEndpoint._M_Ep_Account_PassCode);
	}
	catch (sql::SQLException& pException) {
		std::cout << pException.what() << std::endl;
		return;
	}
	_M_Base->setSchema(pSchema.c_str());
}

connection_base::~connection_base() {
	_M_Base->close();
}