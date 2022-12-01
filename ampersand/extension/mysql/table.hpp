#pragma once
#include <ampersand/extension/mysql/types.hpp>
#include <ampersand/extension/mysql/types_annotation.hpp>

#include <ampersand/extension/mysql/connection.hpp>
#include <ampersand/extension/mysql/table_impl.hpp>

#include <ampersand/meta/body/tag.hpp>
#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

namespace ampersand::extension::mysql {
	template <typename... AnyType>
	class table;

	template <typename... Attributes>
	class table<meta::meta_type<Attributes...>> {
		using __name_tuple = __table_name_tuple<Attributes...>;
		using __string	   = std::string;

			  __name_tuple _M_Name;
			  __string	   _M_Table_Name;
	public:
		using string_type = std::string;

	public:
		template <typename... StringType>
		table(string_type pName, StringType&&... pString) // Create Table
			: _M_Name	   (std::make_tuple(pString...)),
			  _M_Table_Name(pName)						{  }

	public:
		template <typename AttrT>
		string_type& operator[](AttrT);
		string_type& name	   ();
	};

	template <typename... Attribute>
	template <typename AttrT>
	typename table<meta::meta_type<Attribute...>>::string_type&
		table<meta::meta_type<Attribute...>>::operator[](AttrT pAttribute) {
			return
				__name_from_tuple
					(pAttribute, meta::meta_type<Attributes...>{}, _M_Name);
	}

	template <typename... Attribute>
	typename table<meta::meta_type<Attribute...>>::string_type&
		table<meta::meta_type<Attribute...>>::name() {
			return _M_Table_Name;
	}
}