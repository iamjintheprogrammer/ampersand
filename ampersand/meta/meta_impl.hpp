#pragma once
#include <ampersand/meta/meta_function.hpp>

#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

namespace ampersand::meta {
	template <typename... AnyType>
	class meta_impl;

	template 
		<concepts::meta_type MetaType,
			concepts::meta_function... Function>
	class meta_impl<MetaType, Function...> {
		using		type_impl = MetaType;
		using tuple_type_impl = std::tuple<Function...>;

		type_impl       _M_Impl_Type;
		tuple_type_impl _M_Impl_Function;
	public:
		using type = type_impl;
		meta_impl(type pType, Function... pFunction)
			: _M_Impl_Type	  (pType),
			  _M_Impl_Function(pFunction...) {  }

		type type_of() { return _M_Impl_Type; }

		template <std::size_t Idx, typename... AnyType>
		friend auto get_meta_function(meta_impl<AnyType...>&);
	};

	template 
		<concepts::meta_type MetaType,
			concepts::meta_function... Function>
	meta_impl(MetaType, Function...)->meta_impl<MetaType, Function...>;

	template <std::size_t Idx, typename... AnyType>
	auto
		get_meta_function
			(meta_impl<AnyType...>& pMetaImpl) {
		return
			std::get<Idx>
				(pMetaImpl._M_Impl_Function);
	}
}