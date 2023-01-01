#pragma once
#include <stdbool.h>
#include <ampersand/schema/driver/driver_type.h>

bool
	__schema_driver_module_initialize
		(__schema_driver_module*, const char*);

bool
	__schema_driver_controller_initialize
		(__schema_driver_module*, __schema_driver_controller*);

bool
	__schema_driver_module_cleanup
		(__schema_driver_module*);