#pragma once
#include <poly_machine/symbol_type.h>

#define AMPERSAND_OPERAND_ANONYMOUS 0
#define AMPERSAND_OPERAND_NAMED     1

#define AMPERSAND_OPERAND_DYNAMIC   0
#define AMPERSAND_OPERAND_CONSTANT  1

#define AMPERSAND_OPERAND_OBJECT    (1 << 3)
#define AMPERSAND_OPERAND_FUNCTION  (1 << 4)
#define AMPERSAND_OPERAND_PRIMITIVE (1 << 5)

typedef struct
	__ampersand_operand_attribute {
	union {
		uint8_t all_flag;
		struct {
			uint8_t named    : 1, // 1 : Named, 0 : Anonymous
					lifetime : 1, // 0 : Dynamic, 1 : Constant
					category : 7;
		};
	};

}	__ampersand_operand_attribute;

typedef struct
	__ampersand_operand {
	__ampersand_operand_attribute attr;
	union
	{
		__ampersand_symbol_primitive* primitive;
		__ampersand_symbol_function * function ;
		__ampersand_symbol_interface* interface;
	} symbol;

	void*  entity     ;
	size_t entity_size;
}	__ampersand_operand;