#include <poly_machine/symbol_type.h>

__ampersand_symbol_interface*
	__ampersand_symbol_find_interface
		(__ampersand_symbol_table*, const char*);

__ampersand_symbol_function*
	__ampersand_symbol_find_function
		(__ampersand_symbol_table*, const char*);

__ampersand_symbol_variable*
	__ampersand_symbol_find_variable
		(__ampersand_symbol_table*, const char*);

uint64_t
	__ampersand_symbol_count_interface
		(__ampersand_symbol_table*, const char*);

uint64_t
	__ampersand_symbol_count_function
		(__ampersand_symbol_table*, const char*);

uint64_t
	__ampersand_symbol_count_variable
		(__ampersand_symbol_table*, const char*);