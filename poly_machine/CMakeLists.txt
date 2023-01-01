cmake_minimum_required(VERSION 3.12)

project    (ampersand.poly_machine VERSION 0.1.0 LANGUAGES C)
add_library(ampersand.poly_machine STATIC
            symbol_type.h
            symbol_init.h
            symbol_manip.h
            symbol_init.c
            symbol_manip.c
            operand_type.h
            operand_init.h
            operand_manip.h
            operand_init.c
            operand_manip.c
            instruction.h
            instruction_init.h
            instruction_exec.h
            binary_type.h)