cmake_minimum_required(VERSION 3.12)

project    (ampersand.poly VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.poly STATIC
            poly_binary.hpp
            poly_binary.cpp
            poly_object.hpp
            poly_any.hpp
            poly_any.cpp
            machine/instruction.hpp
            machine/instruction_verb.hpp
            machine/instruction.cpp
            machine/format.hpp
            machine/format_category.hpp
            machine/format.cpp
            machine/operand.hpp
            machine/operand.cpp
            machine/format/call.hpp
            machine/format/call.cpp
            machine/format/call_method.hpp
            machine/format/call_method.cpp
            machine/format/primitive_operator.hpp
            machine/format/primitive_operator.cpp
            machine/format/object.hpp
            machine/format/object.cpp
            machine/format/move.hpp
            machine/format/move.cpp
            declare.hpp
            declare.cpp
            fetch.hpp
            fetch.cpp)

set_target_properties(ampersand.poly PROPERTIES LINKER_LANGUAGE CXX)
add_subdirectory(python)