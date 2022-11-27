#pragma once

#include <string>
#include <string_view>

#include <type_table/all.hpp>
#include <meta/attribute.hpp>

namespace ampersand::meta {
	template <typename... T>
	struct field;

	template <typename T, typename... Attribute>
	struct field<T, attribute_set<Attribute...>> {
	public:
		using value_type = std::remove_all_extents_t<T>;
		using attribute  = attribute_set<Attribute...> ;
	};
}