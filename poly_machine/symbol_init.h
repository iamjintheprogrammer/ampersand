#include <poly_machine/symbol_type.h>

void
	__ampersand_symbol_table_initialize
		(__ampersand_symbol_table*);

void
	__ampersand_symbol_table_cleanup
		(__ampersand_symbol_table*);

void
	__ampersand_symbol_interface_initialize
		(__ampersand_symbol_table*, __ampersand_symbol_interface*);

void
	__ampersand_symbol_interface_cleanup
		(__ampersand_symbol_table*, __ampersand_symbol_interface*);

void
	__ampersand_symbol_function_initialize
		(__ampersand_symbol_table*, __ampersand_symbol_function*);

void
	__ampersand_symbol_function_cleanup
		(__ampersand_symbol_table*, __ampersand_symbol_function*);

void
	__ampersand_symbol_variable_initialize
		(__ampersand_symbol_table*, __ampersand_symbol_variable*);

void
	__ampersand_symbol_variable_cleanup
		(__ampersand_symbol_table*, __ampersand_symbol_variable*);