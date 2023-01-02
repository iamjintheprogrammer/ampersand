#pragma once
#include <cstring>
#include <algorithm>

#include <ampersand/meta/body_traits_impl.hpp>
#include <ampersand/meta/meta_object.hpp>

namespace ampersand::meta {
	template <typename... AnyType>
	struct body_traits;

	template <typename... Attributes>
	struct body_traits<meta_type<Attributes...>> {
		using body_type		   = typename details::body_type<meta_type<Attributes...>>::type;
		using meta_object_type = basic_meta_object<meta_type<Attributes...>, body_traits<meta_type<Attributes...>>>;

		template <typename KeyType>  static auto& get(body_type&, KeyType); // For Generic Meta Type
									 static auto& get(body_type&);			 // For Primitive Meta Type

		static void construct(body_type&, const char*) {  }
		static void destruct (body_type&)			   {  }

		template <typename RhsObject>
		static auto
			equal
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator{ meta::equal{}, pLhs, pRhs };
		}

		template <typename RhsObject>
		static auto
			not_equal
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator{ meta::not_equal{}, pLhs, pRhs };
		}

		template <typename RhsObject>
		static auto
			greater_than
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator{ meta::greater_than{}, pLhs, pRhs };
		}

		template <typename RhsObject>
		static auto
			greater_or_equal
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator{ meta::greater_or_equal{}, pLhs, pRhs };
		}

		template <typename RhsObject>
		static auto
			less_than
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator{ meta::less_than{}, pLhs, pRhs };
		}

		template <typename RhsObject>
		static auto
			less_or_equal
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator{ meta::less_or_equal{}, pLhs, pRhs };
		}

		template <typename RhsObject>
		static auto
			add
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator{ meta::add{}, pLhs, pRhs };
		}

		template <typename RhsObject>
		static auto
			add_and_store
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator{ meta::add_and_store{}, pLhs, pRhs };
		}

		template <typename RhsObject>
		static auto
			subtract
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator{ meta::subtract{}, pLhs, pRhs };
		}

		template <typename RhsObject>
		static auto
			subtract_and_store
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator{ meta::subtract_and_store{}, pLhs, pRhs };
		}

		template <typename RhsObject>
		static auto
			multiply
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator{ meta::multiply{}, pLhs, pRhs };
		}

		template <typename RhsObject>
		static auto
			multiply_and_store
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator{ meta::multiply_and_store{}, pLhs, pRhs };
		}

		template <typename RhsObject>
		static auto
			divide
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator{ meta::divide{}, pLhs, pRhs };
		}

		template <typename RhsObject>
		static auto
			divide_and_store
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator{ meta::divide_and_store{}, pLhs, pRhs };
		}

		template <typename RhsObject>
		static auto
			move
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator
					{ meta::move{}, pLhs, pRhs };
		}
		
		template <typename RhsObject>
		static auto
			copy
				(meta_object_type& pLhs, RhsObject&& pRhs) {
			return
				meta_operator
					{ meta::copy{}, pLhs, pRhs };
		}
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
			meta_operator
				{ meta::reference{}, pBody, pKey };
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
}