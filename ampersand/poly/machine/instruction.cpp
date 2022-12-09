#include "instruction.hpp"

namespace ampersand::poly::machine {
	instruction_verb instruction::verb() {
		return _M_InstVerb;
	}
}