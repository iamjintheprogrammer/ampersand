#pragma once
#include <ampersand/diopter/syntax/syntax_element.hpp>

namespace ampersand::diopter::syntax {
	class constant : public element {
		union
		{
			std::int8_t  i8 ; std::uint8_t  u8 ;
			std::int16_t i16; std::uint16_t u16;
			std::int32_t i32; std::uint32_t u32;
			std::int64_t i64; std::uint64_t u64;
			float	     f32; double		f64;
		}						 impl_constant;
		std::string				 impl_constant_string ;
		std::wstring			 impl_constant_wstring;
		meta::primitive_category impl_constant_category;
	public:
		constant(std::integral	     auto);
		constant(std::floating_point auto);

	public:
		meta::primitive_category get_category();
		bool					 get		 (std::integral		  auto&);
		bool					 get		 (std::floating_point auto&);
	};

	constant::constant(std::integral auto pValue)
		: element(element::element_category::constant) {
			using value_type = decltype(pValue);
			if constexpr (std::is_same_v<value_type, std::int8_t>) {
				impl_constant_category = meta::primitive_category::i8;
				impl_constant.i8	   = pValue;
			}
			else if constexpr (std::is_same_v<value_type, std::uint8_t>) {
				impl_constant_category = meta::primitive_category::u8;
				impl_constant.u8	   = pValue;
			}

			else if constexpr (std::is_same_v<value_type, std::int16_t>){
				impl_constant_category = meta::primitive_category::i16;
				impl_constant.i16	   = pValue;
			}
			else if constexpr (std::is_same_v<value_type, std::uint16_t>){
				impl_constant_category = meta::primitive_category::u16;
				impl_constant.u16	   = pValue;
			}

			else if constexpr (std::is_same_v<value_type, std::int32_t>){
				impl_constant_category = meta::primitive_category::i32;
				impl_constant.i32	   = pValue;
			}
			else if constexpr (std::is_same_v<value_type, std::uint32_t>){
				impl_constant_category = meta::primitive_category::u32;
				impl_constant.u32	   = pValue;
			}

			else if constexpr (std::is_same_v<value_type, std::int64_t>){
				impl_constant_category = meta::primitive_category::i64;
				impl_constant.i64	   = pValue;
			}
			else if constexpr (std::is_same_v<value_type, std::uint64_t>){
				impl_constant_category = meta::primitive_category::u64;
				impl_constant.u64	   = pValue;
			}
	}

	constant::constant(std::floating_point auto pValue)
		: element(element::element_category::constant) {
			using value_type = decltype(pValue);
			if constexpr (std::is_same_v<value_type, float>) {
				impl_constant_category = meta::primitive_category::f32;
				impl_constant.f32	   = pValue;
			}
			else if constexpr (std::is_same_v<value_type, double>) {
				impl_constant_category = meta::primitive_category::f64;
				impl_constant.f64	   = pValue;
			}
	}

	bool 
		constant::get
			(std::integral auto& pValue) {
		using value_type = std::remove_reference_t<decltype(pValue)>;
		if constexpr (std::is_same_v<value_type, std::int8_t>) {
			if (impl_constant_category == meta::primitive_category::i8) {
				pValue = impl_constant.i8;
				return true;
			}
		}
		else if constexpr (std::is_same_v<value_type, std::uint8_t>) {
			if (impl_constant_category == meta::primitive_category::u8) {
				pValue = impl_constant.u8;
				return true;
			}
		}

		else if constexpr (std::is_same_v<value_type, std::int16_t>) {
			if (impl_constant_category == meta::primitive_category::i16) {
				pValue = impl_constant.i16;
				return true;
			}
		}
		else if constexpr (std::is_same_v<value_type, std::uint16_t>) {
			if (impl_constant_category == meta::primitive_category::u16) {
				pValue = impl_constant.u16;
				return true;
			}
		}

		else if constexpr (std::is_same_v<value_type, std::int32_t>) {
			if (impl_constant_category == meta::primitive_category::i32) {
				pValue = impl_constant.i32;
				return true;
			}
		}
		else if constexpr (std::is_same_v<value_type, std::uint32_t>) {
			if (impl_constant_category == meta::primitive_category::u32) {
				pValue = impl_constant.u32;
				return true;
			}
		}

		else if constexpr (std::is_same_v<value_type, std::int64_t>) {
			if (impl_constant_category == meta::primitive_category::i64) {
				pValue = impl_constant.i64;
				return true;
			}
		}
		else if constexpr (std::is_same_v<value_type, std::uint64_t>) {
			if (impl_constant_category == meta::primitive_category::u64) {
				pValue = impl_constant.u64;
				return true;
			}
		}

		return false;
	}
	bool 
		constant::get
			(std::floating_point auto& pValue) {
		using value_type = std::remove_reference_t<decltype(pValue)>;
		if constexpr (std::is_same_v<value_type, float>) {
			if (impl_constant_category == meta::primitive_category::f32) {
				pValue = impl_constant.f32;
				return true;
			}
		}
		else if constexpr (std::is_same_v<value_type, float>) {
			if (impl_constant_category == meta::primitive_category::f64) {
				pValue = impl_constant.f64;
				return true;
			}
		}
	}
}