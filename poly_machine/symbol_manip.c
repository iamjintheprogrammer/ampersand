#include <poly_machine/symbol_manip.h>
#include <string.h>

_Thread_local void     (* __fn_find_by_name)(__ampersand_symbol*);
_Thread_local const char* __cond_find_by_name;

_Thread_local void						   (*__fn_find_by_attribute)(__ampersand_symbol*);
_Thread_local __ampersand_symbol_attribute __cond_find_by_attribute;

void
	__ampersand_do_find_by_name
		(__ampersand_symbol* pSymbol) {
	if (!strcmp(pSymbol->name, __cond_find_by_name))
		__fn_find_by_name(pSymbol);
}

void
	__ampersand_do_find_by_attribute
		(__ampersand_symbol* pSymbol) {
	if(pSymbol->attr.category
			== __cond_find_by_attribute.category)
				__fn_find_by_attribute(pSymbol);
}

void
	__ampersand_symbol_find_by_name
		(__ampersand_symbol_table* pTable,
		 const char*			   pName ,
		 void					 (*pExec)(__ampersand_symbol*)) {
	crisp_list_iterator				      sym_begin, sym_end;
	crisp_list_begin   (&pTable->symbol, &sym_begin);
	crisp_list_end	   (&pTable->symbol, &sym_end)  ;

	  __fn_find_by_name = pExec;
	__cond_find_by_name = pName;

	crisp_list_for_each
		(&sym_begin, &sym_end, &__ampersand_do_find_by_name);
}

void
	__ampersand_symbol_find_by_attribute
		(__ampersand_symbol_table*    pTable    ,
		 __ampersand_symbol_attribute pAttribute,
		 void						(*pExec)(__ampersand_symbol*)) {
	crisp_list_iterator				      sym_begin, sym_end;
	crisp_list_begin   (&pTable->symbol, &sym_begin);
	crisp_list_end	   (&pTable->symbol, &sym_end)  ;

	  __fn_find_by_attribute = pExec	 ;
	__cond_find_by_attribute = pAttribute;
	
	crisp_list_for_each
		(&sym_begin, &sym_end, &__ampersand_do_find_by_attribute);
}