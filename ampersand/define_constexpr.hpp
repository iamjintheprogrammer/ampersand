#pragma once

#define AMPERSAND_CONST_MEMBER(type, name, value) static constexpr type name = value;
#define AMPERSAND_CONST_INLINNE(type, name, value) inline constexpr type name = value;