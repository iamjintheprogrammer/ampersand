#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/attribute.hpp>

namespace ampersand::extension::mysql {
	template <std::size_t N, typename... Annotation> using    varchar_t = meta::attribute<char[N], annotation::mysql_type, Annotation...>;
	template <std::size_t N, typename... Annotation> using char_array_t = meta::attribute<char[N], annotation::mysql_type, Annotation...>;
	
	template <typename... Annotation> using	  	             tiny_int_t = meta::attribute<std::int8_t , annotation::mysql_type, Annotation...>;
	template <typename... Annotation> using			unsigned_tiny_int_t = meta::attribute<std::uint8_t, annotation::mysql_type, Annotation...>;

	template <typename... Annotation> using					small_int_t = meta::attribute<std::int16_t , annotation::mysql_type, Annotation...>;
	template <typename... Annotation> using		   unsigned_small_int_t = meta::attribute<std::uint16_t, annotation::mysql_type, Annotation...>;
	
	template <typename... Annotation> using				   normal_int_t = meta::attribute<std::int32_t , annotation::mysql_type, Annotation...>;
	template <typename... Annotation> using		  unsigned_normal_int_t = meta::attribute<std::uint32_t, annotation::mysql_type, Annotation...>;

	template <typename... Annotation> using					  big_int_t = meta::attribute<std::int64_t , annotation::mysql_type, Annotation...>;
	template <typename... Annotation> using		     unsigned_big_int_t = meta::attribute<std::uint64_t, annotation::mysql_type, Annotation...>;

	template <std::size_t N, typename... Annotation> inline constexpr    varchar_t<N, annotation::mysql_type, Annotation...> varchar;
	template <std::size_t N, typename... Annotation> inline constexpr char_array_t<N, annotation::mysql_type, Annotation...> char_array;

	template <typename... Annotation> inline constexpr          tiny_int_t<annotation::mysql_type, Annotation...>		   tiny_int;
	template <typename... Annotation> inline constexpr unsigned_tiny_int_t<annotation::mysql_type, Annotation...> unsigned_tiny_int;

	template <typename... Annotation> inline constexpr          small_int_t<annotation::mysql_type, Annotation...>		   small_int;
	template <typename... Annotation> inline constexpr unsigned_small_int_t<annotation::mysql_type, Annotation...> unsigned_small_int;

	template <typename... Annotation> inline constexpr          normal_int_t<annotation::mysql_type, Annotation...>		   normal_int;
	template <typename... Annotation> inline constexpr unsigned_normal_int_t<annotation::mysql_type, Annotation...> unsigned_normal_int;

	template <typename... Annotation> inline constexpr          big_int_t<annotation::mysql_type, Annotation...>		   big_int;
	template <typename... Annotation> inline constexpr unsigned_big_int_t<annotation::mysql_type, Annotation...> unsigned_big_int;
}