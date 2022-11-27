#pragma once

#include <meta/field.hpp>
#include <meta/field_utility.hpp>

namespace ampersand::meta {
	template <typename... T>
	class meta_type;

	template <typename... Fields, typename... Attributes>
	class meta_type<field_table<Fields...>, Attributes...> {
		using __field_table = field_table<Fields...>;
			  __field_table _M_Field;
	public:
		constexpr meta_type(field_table<Fields...>& pFieldTable)
			: _M_Field(pFieldTable) {}

	public:
		static constexpr auto& get_field_table  () { return _M_Field; }
	};
}