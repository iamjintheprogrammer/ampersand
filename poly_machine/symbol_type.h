#pragma once
#include <stdint.h>
#include <stddef.h>

#include <crisp/list/list.h>
#include <crisp/list/list_iterate.h>

#define AMPERSAND_SYMBOL_INTERFACE  1
#define AMPERSAND_SYMBOL_PRIMITIVE (1 << 1)
#define AMPERSAND_SYMBOL_VARIABLE  (1 << 2)
#define AMPERSAND_SYMBOL_FUNCTION  (1 << 3)

#define AMPERSAND_PRIMITIVE_I8   0
#define AMPERSAND_PRIMITIVE_U8   1

#define AMPERSAND_PRIMITIVE_I16  2
#define AMPERSAND_PRIMITIVE_U16  3

#define AMPERSAND_PRIMITIVE_I32  4
#define AMPERSAND_PRIMITIVE_U32  5

#define AMPERSAND_PRIMITIVE_I64  6
#define AMPERSAND_PRIMITIVE_U64  7

#define AMPERSAND_PRIMITIVE_F32  8
#define AMPERSAND_PRIMITIVE_F64  9

#define AMPERSAND_PRIMITIVE_STR  10
#define AMPERSAND_PRIMITIVE_WSTR 11

typedef struct
	__ampersand_symbol_attribute {
		uint8_t category;
}	__ampersand_symbol_attribute;

typedef struct
	__ampersand_symbol {
	crisp_list_node				 node;

	__ampersand_symbol_attribute attr;
	const char*					 name;
	size_t						 name_length;
}	__ampersand_symbol;

typedef struct
	__ampersand_symbol_interface {
	__ampersand_symbol head; // Name of the Interface
	
	crisp_list		   func		  ,
					   func_static,

					   attr		  ,
					   attr_static;
}	__ampersand_symbol_interface;

typedef struct
	__ampersand_symbol_primitive {
	__ampersand_symbol head; // Name of the Interface

	uint8_t		       category;
	size_t			   actual_size;
}	__ampersand_symbol_primitive;

typedef struct
	__ampersand_symbol_variable {
	__ampersand_symbol head;
	size_t			   actual_size;
}	__ampersand_symbol_variable;

typedef struct
	__ampersand_symbol_function {
	__ampersand_symbol head;
}	__ampersand_symbol_function;

typedef struct
	__ampersand_symbol_table {
	crisp_list sym_interface,
			   sym_func		,
			   sym_variable ;
}	__ampersand_symbol_table;