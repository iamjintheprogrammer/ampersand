#pragma once
#include <cstdint>
#include <cstddef>

namespace ampersand::poly::machine {
	enum class instruction_verb    {
		enter, leave,
		
		call,
		call_method,
		
		ob_create   ,
		ob_delete   ,
		ob_reference,

		op_add  ,
		op_addeq,
		
		op_sub  ,
		op_subeq,
		
		op_mul  ,
		op_muleq,
		
		op_div  ,
		op_diveq,

		move, move_shallow, move_deep
	};
}