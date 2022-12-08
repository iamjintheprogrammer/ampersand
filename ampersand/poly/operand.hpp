#pragma once
#include <string>

namespace ampersand::poly {
	class operand {
	public:
		enum class category {
			operand  ,
			void_type
		};

		using string_type = std::string;
		operand(string_type, string_type);
		operand();

		string_type& name	     ();
		string_type& type_name   ();
		category     get_category();

	private:
		using __string_type = std::string;
			  __string_type _M_Typename,
							_M_Name	   ;
			  category      _M_Category;
	};
}