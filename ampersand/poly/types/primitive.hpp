#pragma once
#include <ampersand/poly/types/integral.hpp>
#include <ampersand/poly/types/floating_point.hpp>

namespace ampersand::poly {
	using i8 = poly_object<std::int8_t> ;
	using u8 = poly_object<std::uint8_t>;

	using i16 = poly_object<std::int16_t> ;
	using u16 = poly_object<std::uint16_t>;

	using i32 = poly_object<std::int32_t> ;
	using u32 = poly_object<std::uint32_t>;

	using i64 = poly_object<std::int64_t> ;
	using u64 = poly_object<std::uint64_t>;

	using f32 = poly_object<float>;
	using f64 = poly_object<double>;
}