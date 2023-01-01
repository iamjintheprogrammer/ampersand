#include "driver.h"
#include <Windows.h>

bool
	__schema_driver_module_initialize
		(__schema_driver_module* pModule, const char* pPath) {
	pModule->path   = pPath;
	pModule->handle = LoadLibraryA(pPath);

	return (pModule->handle != 0);
}

bool
	__schema_driver_controller_initialize
		(__schema_driver_module*	 pModule,
		 __schema_driver_controller* pController) {
	pController->open  = GetProcAddress(pModule->handle, SCHEMA_DRIVER_FUNC_OPEN);
	pController->close = GetProcAddress(pModule->handle, SCHEMA_DRIVER_FUNC_CLOSE);

	return (pController->open && pController->close);
}

bool
	__schema_driver_module_cleanup
		(__schema_driver_module* pModule) {
	FreeLibrary(pModule->handle);
}