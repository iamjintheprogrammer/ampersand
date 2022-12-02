#include "driver.hpp"

ampersand::extension::mysql::driver::driver()
	: _M_Base(sql::mysql::get_driver_instance()) { }