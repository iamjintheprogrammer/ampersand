#pragma once
#include <cstring>
#include <algorithm>

#include <ampersand/meta/details/body_traits_impl.hpp>
#include <ampersand/meta/meta_object.hpp>

namespace ampersand::meta {
	template <typename... AnyType>
	struct body_traits;

	template <typename... Attributes>
	struct body_traits<meta_type<Attributes...>> {
		using body_type = typename details::body_type<meta_type<Attributes...>>::type;

		template <typename KeyType>  static auto& get(body_type&, KeyType); // For Generic Meta Type
									 static auto& get(body_type&);			// For Primitive Meta Type

		template <typename BodyType> static auto  greater_than    (body_type&, BodyType&&);
		template <typename BodyType> static auto  greater_or_equal(body_type&, BodyType&&);

		template <typename BodyType> static auto  less_than	      (body_type&, BodyType&&);
		template <typename BodyType> static auto  less_or_equal   (body_type&, BodyType&&);

		template <typename BodyType> static auto  equal			  (body_type&, BodyType&&);
		template <typename BodyType> static auto  not_equal		  (body_type&, BodyType&&);
 
		template <typename BodyType> static auto  clone(body_type&, BodyType&&);
		template <typename BodyType> static auto  copy (body_type&, BodyType&&);
		template <typename BodyType> static auto  move (body_type&, BodyType&&);
	};

	template <typename... Attributes>
	template <typename KeyType>
	auto&
		body_traits<meta_type<Attributes...>>::get 
			(body_type& pBody, KeyType pKey) {
		static_assert
			(!utility::is_primitive_type_v<meta_type<Attributes...>>,
				"[AMPERSAND][BODY_TRAITS] Primitive Meta Type Does not Support Key-Base Acquisition.");
		return
			*reinterpret_cast<basic_meta_object
				<typename KeyType::value_type, body_traits<typename KeyType::value_type>>*>
					(reinterpret_cast<std::uint8_t*>(pBody)
						+ details::body_offset<0, KeyType, Attributes...>::value);
	}

	template <typename... Attributes>
	auto&
		body_traits<meta_type<Attributes...>>::get
			(body_type& pBody) {
		static_assert
			(utility::is_primitive_type_v<meta_type<Attributes...>>,
				"[AMPERSAND][BODY_TRAITS] Non - Primitive Meta Type Does not Support Value Acquisition.");
		return 
			*reinterpret_cast
				<meta_type<Attributes...>::pointer>
					(pBody);
	}

	template <typename... Attributes>
	template <typename BodyType>
	auto
		body_traits<meta_type<Attributes...>>::greater_than
			(body_type& pLhs, BodyType&& pRhs) {
		return;
	}

	template <typename... Attributes>
	template <typename BodyType>
	auto
		body_traits<meta_type<Attributes...>>::greater_or_equal
			(body_type& pLhs, BodyType&& pRhs) {
		return;
	}

	template <typename... Attributes>
	template <typename BodyType>
	auto
		body_traits<meta_type<Attributes...>>::less_than
			(body_type& pLhs, BodyType&& pRhs) {
		return;
	}

	template <typename... Attributes>
	template <typename BodyType>
	auto
		body_traits<meta_type<Attributes...>>::less_or_equal
			(body_type&, BodyType&&) {
		return;
	}

	template <typename... Attributes>
	template <typename BodyType>
	auto
		body_traits<meta_type<Attributes...>>::equal
			(body_type&, BodyType&&) {
		return;
	}

	template <typename... Attributes>
	template <typename BodyType>
	auto
		body_traits<meta_type<Attributes...>>::not_equal
			(body_type&, BodyType&&) {
		return;
	}

	template <typename... Attributes>
	template <typename BodyType>
	auto
		body_traits<meta_type<Attributes...>>::move
			(body_type& pLhs, BodyType&& pRhs) {
		if constexpr
			(!std::is_array_v
				<std::remove_reference_t<BodyType>>)
					return;
		
		std::memcpy
			(pLhs, pRhs, std::min(sizeof(body_type), sizeof(BodyType)));
	}

	template <typename... Attributes>
	template <typename BodyType>
	auto
		body_traits<meta_type<Attributes...>>::clone
			(body_type& pLhs, BodyType&& pRhs) {
		if constexpr
			(!std::is_array_v
				<std::remove_reference_t<BodyType>>)
					return;
		
		std::memcpy
			(pLhs, pRhs, std::min(sizeof(body_type), sizeof(BodyType)));
	}

	template <typename... Attributes>
	template <typename BodyType>
	auto
		body_traits<meta_type<Attributes...>>::copy
			(body_type& pLhs, BodyType&& pRhs) {
		if constexpr
			(!std::is_array_v
				<std::remove_reference_t<BodyType>>)
					return;
		
		std::memcpy
			(pLhs, pRhs, std::min(sizeof(body_type), sizeof(BodyType)));
	}
}