#pragma once
#include <variant>

#include <ampersand/meta.hpp>
#include <ampersand/diopter/type_impl.hpp>

namespace ampersand::diopter {
	class type {
		friend class symbol;
		type_impl::type_ptr _M_Impl;

		type(type_impl::type_ptr);
		type();
	public:
		using name_type = type_impl::name_type;

		template <typename... T> type(meta::meta_type<T...>&)		  ;
								 type(meta::meta_type<>&)			  ;
								 type(meta::concepts::primitive auto&);

	public:
		name_type name		   ();
		bool	  link_type    (name_type, type&);
		bool	  primitive	   ();
		type	  operator[]   (name_type);
				  operator bool();
	};

	template <typename... T>
	type::type(meta::meta_type<T...>& pInitType)
		: _M_Impl(std::make_shared<type_impl>(pInitType)) { }
	type::type(meta::concepts::primitive auto& pInitType)
		: _M_Impl(std::make_shared<type_impl>(pInitType)) { }
}