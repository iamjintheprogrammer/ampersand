#include <poly_machine/symbol_init.h>

void
	__ampersand_symbol_table_initialize
		(__ampersand_symbol_table* pTable) {
	crisp_list_initialize(&pTable->symbol);
	pTable->symbol_count = 0;
}

void
	__ampersand_symbol_table_cleanup
		(__ampersand_symbol_table* pTable) {
}

void
	__ampersand_symbol_initialize
		(__ampersand_symbol_table* pTable,
		 __ampersand_symbol*	   pSymbol) {
	crisp_list_push_back(&pTable->symbol, pSymbol);
}

void
	__ampersand_symbol_cleanup
		(__ampersand_symbol_table* pTable, __ampersand_symbol* pSymbol) {
	crisp_list_pop_at(&pTable->symbol, &pSymbol->node);
}