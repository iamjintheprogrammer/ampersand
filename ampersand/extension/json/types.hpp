#pragma once
#include <ampersand/meta/attribute.hpp>

namespace ampersand::extension::json {
	inline constexpr meta::attribute<std::int32_t> int32;
	inline constexpr meta::attribute<std::int32_t> int64;
	
	inline constexpr meta::attribute<std::int32_t> uint32;
	inline constexpr meta::attribute<std::int32_t> uint64;

	template <typename ArrayT, std::size_t ArraySize>
	using array  = meta::attribute<ArrayT[ArraySize]>;
}