#include "driver.hpp"

ampersand::extension::mysql::driver::driver()
	: _M_Base(get_driver_instance()) { }