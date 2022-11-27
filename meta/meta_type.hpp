#pragma once

#include <meta/field.hpp>
#include <meta/field_utility.hpp>

namespace ampersand::meta {
	template <typename... T>
	class meta_type;

	template <typename... Attributes, typename... Fields>
	class meta_type<attribute_set<Attributes...>, Fields...> {
	public:
		using attribute = attribute_set<Attributes...>;
		constexpr meta_type
			(const attribute& pAttributes, const Fields&... pField)	{}
	};

	template <typename... Attributes, typename... Fields>
	meta_type
		(const attribute_set<Attributes...>&, const Fields&...)
			-> meta_type<attribute_set<Attributes...>, Fields...>;
}