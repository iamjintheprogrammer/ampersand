#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/attribute.hpp>

namespace ampersand::extension::mysql {
	template <std::size_t N, typename... Annotation> using    varchar_t = meta::attribute<char[N], Annotation...>;
	template <std::size_t N, typename... Annotation> using char_array_t = meta::attribute<char[N], Annotation...>;
	
	template <typename... Annotation> using	  	             tiny_int_t = meta::attribute<std::int8_t , Annotation...>;
	template <typename... Annotation> using			unsigned_tiny_int_t = meta::attribute<std::uint8_t, Annotation...>;

	template <typename... Annotation> using					small_int_t = meta::attribute<std::int16_t , Annotation...>;
	template <typename... Annotation> using		   unsigned_small_int_t = meta::attribute<std::uint16_t, Annotation...>;
	
	template <typename... Annotation> using				   normal_int_t = meta::attribute<std::int32_t , Annotation...>;
	template <typename... Annotation> using		  unsigned_normal_int_t = meta::attribute<std::uint32_t, Annotation...>;

	template <typename... Annotation> using					  big_int_t = meta::attribute<std::int64_t , Annotation...>;
	template <typename... Annotation> using		     unsigned_big_int_t = meta::attribute<std::uint64_t, Annotation...>;

	template <std::size_t N, typename... Annotation> inline constexpr    varchar_t<N, Annotation...> varchar;
	template <std::size_t N, typename... Annotation> inline constexpr char_array_t<N, Annotation...> char_array;

	template <typename... Annotation> inline constexpr          tiny_int_t<Annotation...>		   tiny_int;
	template <typename... Annotation> inline constexpr unsigned_tiny_int_t<Annotation...> unsigned_tiny_int;

	template <typename... Annotation> inline constexpr          small_int_t<Annotation...>		   small_int;
	template <typename... Annotation> inline constexpr unsigned_small_int_t<Annotation...> unsigned_small_int;

	template <typename... Annotation> inline constexpr          normal_int_t<Annotation...>		   normal_int;
	template <typename... Annotation> inline constexpr unsigned_normal_int_t<Annotation...> unsigned_normal_int;

	template <typename... Annotation> inline constexpr          big_int_t<Annotation...>		   big_int;
	template <typename... Annotation> inline constexpr unsigned_big_int_t<Annotation...> unsigned_big_int;
}