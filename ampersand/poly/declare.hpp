#pragma once
#include <string>
#include <vector>

namespace ampersand::poly {
	class declare {
	public:
		using string_type = std::string;
		using index_type  = std::size_t;
		using size_type   = std::size_t;

		class attribute {
			using __string_type = std::string;
				  __string_type _M_Name, _M_Type;
		public:
			using string_type = std::string;
			attribute(string_type, string_type);

		public:
			string_type		 name();
			string_type type_name();
		};

	public:
		template <typename... Attributes>
		declare(string_type, Attributes&&...);

		size_type  attribute_count();
		attribute& operator[]	  (index_type);

	private:
		using __attrvec = std::vector<attribute>;
			  __attrvec   _M_Attributes;
			  string_type _M_Name	   ;
	};

	template <typename... Attributes>
	declare::declare
		(string_type pName, Attributes&&... pAttribute)
			 : _M_Name(pName) {
		((_M_Attributes.push_back(pAttribute)), ...);
	}
}