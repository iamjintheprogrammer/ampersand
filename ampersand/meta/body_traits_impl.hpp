#pragma once
#include <concepts>
#include <ampersand/meta/meta.hpp>

namespace ampersand::meta::details {
	template <std::size_t Size, typename... AnyType>
	struct body_size;

	template <std::size_t Size, std::integral IntegralType>
	struct body_size
		<Size, meta_type<IntegralType>>
			: std::integral_constant
				<std::size_t,
				 Size + sizeof(IntegralType)> {};
	template <std::size_t Size, std::floating_point FloatType>
	struct body_size
		<Size, meta_type<FloatType>>
			: std::integral_constant
				<std::size_t,
				 Size + sizeof(FloatType)> {};
	template <std::size_t Size, typename... MetaAttribute>
	struct body_size
		<Size, meta_type<MetaAttribute...>>
			: std::integral_constant
				<std::size_t,
				 body_size<Size, typename MetaAttribute::value_type...>::value> {};
	template 
		<std::size_t Size,
		 typename... MetaAttribute,
		 typename... Remaining>
	struct body_size
		<Size, meta_type<MetaAttribute...>, Remaining...>
			: std::integral_constant
				<std::size_t,
				 Size + body_size<0, meta_type<MetaAttribute...>>::value
					  + body_size<0, Remaining...>				 ::value> {};

	template <std::size_t Size, typename... AnyType>
	struct body_offset;

	template
		<std::size_t Size,
		 typename    Target,
		 typename    Attribute,
		 typename... Remaining>
	struct body_offset
		<Size, Target, Attribute, Remaining...>
			: body_offset
				<Size + body_size<0, typename Attribute::value_type>::value,
				 Target,
				 Remaining...> {};

	template
		<std::size_t Size,
		 typename    Target   ,
		 typename... Remaining>
	struct body_offset
		<Size, Target, Target, Remaining...>
			: std::integral_constant
				<std::size_t, Size> {};

	template <std::size_t Size, typename Target>
	struct body_offset
		<Size, Target>
			:  std::integral_constant<std::size_t, Size> {};

	template <typename MetaType>
	struct body_type {
		using type = std::uint8_t[body_size<0, MetaType>::value];
	};
}