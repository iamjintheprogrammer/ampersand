#include "symbol_result.hpp"

namespace ampersand::diopter {
	const char* impl_result_message_table[] = {
		"Successful"				,
		"Symbol Not Found"			,
		"Duplicated Declaration"	,
		"Attribute Symbol Not Found",
		"Argument Symbol Not Found" ,
		"Return Symbol Not Found"
	};

	symbol_result::result_code
		symbol_result::result() {
			return impl_result_code;
	}

	symbol_result::message_type
		symbol_result::result_message() {
			return
				impl_result_message_table
					[(std::underlying_type_t<result_code>)impl_result_code];
	}

	symbol_result::operator bool() {
			return impl_result_code == result_code_impl::success;
	}

	bool
		symbol_result::operator==
			(symbol_result& pResult) {
		return impl_result_code == pResult.impl_result_code;
	}
	
	bool
		symbol_result::operator!=
			(symbol_result& pResult) {
		return impl_result_code != pResult.impl_result_code;
	}
}