#pragma once

#include <string>
#include <string_view>

#include <type_table/all.hpp>
#include <meta/attribute.hpp>

namespace ampersand::meta {
	template <typename... T>
	class field;

	template <typename T, typename... Attribute>
	class field<T, attribute_set<Attribute...>> {
		template <typename... T>
		friend class field;
		using __sv = std::string_view;
			  __sv _M_Name;
	public:
		using value_type = std::remove_all_extents_t<T>;
		using attribute  = attribute_set<Attribute...> ;

		template <typename... T>
		constexpr field(const field<T...>& pCopy) : _M_Name(pCopy._M_Name) {}
		constexpr field(const field& pCopy)	      : _M_Name(pCopy._M_Name) {}
		constexpr field(const char* pName)        : _M_Name(pName) 		   {}

		static constexpr const auto& 
			get_name(const field& pField) { return pField._M_Name; }
		static constexpr const auto
			get_attribute_set()		{ return typename field::attribute{}; }
	};
}