#pragma once
#include <ampersand/meta/meta_object_base.hpp>

namespace ampersand::meta {
	template
		<std::size_t Idx,
			typename LBodyT, typename... LAttributeT,
			typename RBodyT, typename... RAttributeT>
	void
		__adapt_object_impl
			(meta_object_base<LBodyT, meta_type<LAttributeT...>>& pLhs,
			 meta_object_base<RBodyT, meta_type<RAttributeT...>>& pRhs) {
		using attr_left
				= boost::mp11::mp_at_c
					<typename meta_type<LAttributeT...>::type, Idx>;
		using attr_right
				= boost::mp11::mp_at_c
					<typename meta_type<RAttributeT...>::type, Idx>;

		pLhs._M_Get(attr_left{}) = pRhs._M_Get(attr_right{});
	}

	template
		<typename LBodyT, typename... LAttributeT,
		 typename RBodyT, typename... RAttributeT>
	void
		__adapt_object
			(meta_object_base<LBodyT, meta_type<LAttributeT...>>& pLhs,
			 meta_object_base<RBodyT, meta_type<RAttributeT...>>& pRhs) {
		[&pLhs, &pRhs] <std::size_t... Idx>
			(std::index_sequence<Idx...>) {
			(__adapt_object_impl<Idx>(pLhs, pRhs), ...);
		}(std::make_index_sequence<sizeof...(LAttributeT)>{});
	}
}