#pragma once
#include <stdint.h>
#include <stddef.h>

typedef void* __schema_driver_handle;

#define SCHEMA_DRIVER_LOCAL   0
#define SCHEMA_DRIVER_NETWORK 1 // Specify Location Type

#define SCHEMA_DRIVER_FUNC_OPEN  "ampersand_driver_initialize" // Initialize Driver
#define SCHEMA_DRIVER_FUNC_CLOSE "ampersand_driver_cleanup"	   // Cleanup

typedef struct
	__schema_driver_initarg {
		uint8_t type;
		union  {
			struct {
				const char* url		 ,
						  * user_name,
						  * passcode ;
			} network; // Most DBMS

			struct {
				const char* path;
			} local; // Local DB Like SQLite3.
		};
}	__schema_driver_initarg;

typedef struct
	__schema_driver_module {
		const char* path;
		void	  * handle;
}	__schema_driver_module;

typedef struct
	__schema_driver_controller {
		int (*open) (__schema_driver_handle*, __schema_driver_initarg*);
		int (*close)(__schema_driver_handle*);
}	__schema_driver_controller;