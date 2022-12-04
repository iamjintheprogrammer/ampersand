#pragma once
#include <ampersand/schema/table_impl.hpp>

#include <ampersand/meta/body/tag.hpp>
#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

namespace ampersand::schema {
	template <typename... AnyType>
	class table;

	template <typename StringType, typename... Attributes>
	class table<StringType, meta::meta_type<Attributes...>> {
		using __name_tuple = __table_name_tuple<Attributes...>::type;
		using __string	   = std::string;

			  __name_tuple _M_Name		;
			  __string	   _M_Table_Name;
	public:
		using string_type = StringType;

	public:
		template <typename... ArgString>
		table(meta::meta_type<Attributes...>, string_type, ArgString&&...); // Create Table

	public:
		template <typename AttrT>
		string_type& operator[](AttrT);
		string_type& name	   ();
	};

	template <typename StringType, typename... Attributes>
	template <typename... ArgString>
	table<StringType, meta::meta_type<Attributes...>>::table
		(meta::meta_type<Attributes...>,
			string_type pName, ArgString&&... pString) // Create Table
			: _M_Table_Name(pName) {
		if constexpr (sizeof...(ArgString) == sizeof...(Attributes))
			_M_Name = std::make_tuple(string_type(pString)...);
	}

	template <typename StringType, typename... Attributes>
	template <typename AttrT>
	typename table<StringType, meta::meta_type<Attributes...>>::string_type&
		table<StringType, meta::meta_type<Attributes...>>::operator[](AttrT pAttribute) {
			return
				__name_from_tuple
					(pAttribute, meta::meta_type<Attributes...>{}, _M_Name);
	}

	template <typename StringType, typename... Attributes>
	typename table<StringType, meta::meta_type<Attributes...>>::string_type&
		table<StringType, meta::meta_type<Attributes...>>::name() {
			return _M_Table_Name;
	}

	template <typename MetaType, typename StringType, typename... ArgString>
	table(MetaType, StringType, ArgString&&...) -> table<StringType, MetaType>;
}