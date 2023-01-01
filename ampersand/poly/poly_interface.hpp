#pragma once
#include <ampersand/poly/poly_interface_impl.hpp>

namespace ampersand::poly {
	template <typename... AnyType>
	class poly_interface;

	template <typename... Attributes>
	class poly_interface<meta::meta_type<Attributes...>> {
		using __name_table_type = __name_tuple<std::tuple<>, Attributes...>::type;
		using     __string_type = std::string;
		
		__name_table_type _M_Attributes;
		__string_type     _M_Name;

	public:
		using string_type = __string_type;

		template <typename... String>
		poly_interface(string_type, String&&...);
		template <typename Attr>
		string_type operator[](Attr);
		string_type name	  ();
	};

	template <typename... Attributes>
	template <typename... String>
	poly_interface<meta::meta_type<Attributes...>>::poly_interface
		(string_type pName, String&&... pAttributeName)
			: _M_Name(pName) {
		static_assert
			(sizeof...(Attributes) == sizeof...(String),
				"[AMPERSAND][POLY] Attribute Name Not Initialized");

		_M_Attributes = std::make_tuple(pAttributeName...);
	}

	template <typename... Attributes>
	template <typename Attr>
	poly_interface<meta::meta_type<Attributes...>>::string_type
		poly_interface<meta::meta_type<Attributes...>>::operator[](Attr) {
			return std::get
					<boost::mp11::mp_find
						<boost::mp11::mp_list<Attributes...>, Attr>::value>
							(_M_Attributes);
	}

	template <typename... Attributes>
	poly_interface<meta::meta_type<Attributes...>>::string_type
		poly_interface<meta::meta_type<Attributes...>>::name() {
			return _M_Name;
	}
}