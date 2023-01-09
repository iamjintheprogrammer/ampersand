#pragma once
#include <string_view>

namespace ampersand::diopter {
	class symbol_result {
		friend class symbol;

		using      string_view_impl = std::string_view;
		enum class result_code_impl {
			success,
			
			symbol_not_found		  ,
			duplicated_declaration	  ,
			attribute_symbol_not_found,
			argument_symbol_not_found ,
			return_symbol_not_found 
		};

		string_view_impl impl_result_message;
		result_code_impl impl_result_code;

		symbol_result(result_code_impl);
	public:
		using result_code  = result_code_impl;
		using message_type = string_view_impl;

		result_code  result		   ();
		message_type result_message();

			 operator bool();
		bool operator==   (symbol_result&);
		bool operator!=   (symbol_result&);
	};
}