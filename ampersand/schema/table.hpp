#pragma once
#include <ampersand/schema/table_impl.hpp>

#include <ampersand/meta/body/tag.hpp>
#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

namespace ampersand::schema {
	template <typename... AnyType>
	class table;

	template <typename... Attributes>
	class table<meta::meta_type<Attributes...>> {
		using __name_tuple = __table_name_tuple<Attributes...>::type;
		using __string	   = std::string;

			  __name_tuple _M_Name;
			  __string	   _M_Table_Name;
	public:
		using string_type = std::string;

	public:
		template <typename... StringType>
		table(string_type, StringType&&...); // Create Table
		table(string_type);

	public:
		template <typename AttrT>
		string_type& operator[](AttrT);
		string_type& name	   ();
	};

	template <typename... Attributes>
	template <typename... StringType>
	table<meta::meta_type<Attributes...>>::table
		(string_type pName, StringType&&... pString) // Create Table
			: _M_Table_Name(pName) {
		if constexpr (sizeof...(StringType) == sizeof...(Attributes))
			_M_Name = std::make_tuple(pString...);
	}

	template <typename... Attributes>
	table<meta::meta_type<Attributes...>>::table(string_type pName)
		: _M_Table_Name(pName) {}

	template <typename... Attribute>
	template <typename AttrT>
	typename table<meta::meta_type<Attribute...>>::string_type&
		table<meta::meta_type<Attribute...>>::operator[](AttrT pAttribute) {
			return
				__name_from_tuple
					(pAttribute, meta::meta_type<Attribute...>{}, _M_Name);
	}

	template <typename... Attribute>
	typename table<meta::meta_type<Attribute...>>::string_type&
		table<meta::meta_type<Attribute...>>::name() {
			return _M_Table_Name;
	}
}