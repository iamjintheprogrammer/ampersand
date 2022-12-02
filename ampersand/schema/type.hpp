#pragma once
#include <ampersand/meta/attribute.hpp>
#include <ampersand/schema/field.hpp>

namespace ampersand::schema {
namespace types				{
	template <std::size_t VarcharSize, typename... Annotation>
	struct variable_string : field<meta::attribute<char[VarcharSize]>> {};
	template <std::size_t VarcharSize, typename... Annotation>
	struct		    string : field<meta::attribute<char[VarcharSize]>> {};

	template <typename... Annotation>
	using tiny_int_t		  = field<meta::attribute<std::int8_t , Annotation...>>;
	template <typename... Annotation>
	using unsigned_tiny_int_t = field<meta::attribute<std::uint8_t, Annotation...>>;

	template <typename... Annotation>
	using small_int_t		   = field<meta::attribute<std::int16_t , Annotation...>>;
	template <typename... Annotation>
	using unsigned_small_int_t = field<meta::attribute<std::uint16_t, Annotation...>>;

	template <typename... Annotation>
	using normal_int_t			= field<meta::attribute<std::int32_t, Annotation...>>;
	template <typename... Annotation>
	using unsigned_normal_int_t = field<meta::attribute<std::uint32_t, Annotation...>>;

	template <typename... Annotation>
	using		   big_int_t = field<meta::attribute<std::int64_t , Annotation...>>;
	template <typename... Annotation>
	using unsigned_big_int_t = field<meta::attribute<std::uint64_t, Annotation...>>;

	template <typename T, T Value>
	struct constant : std::integral_constant<T, Value> { };
}

	template <std::size_t N, typename... Annotation> 
	inline constexpr types::variable_string<N, Annotation...> varchar	 {};
	template <std::size_t N, typename... Annotation> 
	inline constexpr		  types::string<N, Annotation...> char_array {};

	template <typename... Annotation> inline constexpr types::		   tiny_int_t<Annotation...>		      tiny_int{};
	template <typename... Annotation> inline constexpr types::unsigned_tiny_int_t<Annotation...>     unsigned_tiny_int{};

	template <typename... Annotation> inline constexpr types::		   small_int_t<Annotation...>		     small_int{};
	template <typename... Annotation> inline constexpr types::unsigned_small_int_t<Annotation...>   unsigned_small_int{};

	template <typename... Annotation> inline constexpr types::		  normal_int_t <Annotation...>		    normal_int{};
	template <typename... Annotation> inline constexpr types::unsigned_normal_int_t<Annotation...> unsigned_normal_int{};

	template <typename... Annotation> inline constexpr types::		   big_int_t<Annotation...>				   big_int{};
	template <typename... Annotation> inline constexpr types::unsigned_big_int_t<Annotation...>		  unsigned_big_int{};
}