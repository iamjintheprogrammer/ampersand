#pragma once
#include <variant>

#include <ampersand/meta.hpp>
#include <ampersand/diopter/type_impl.hpp>

namespace ampersand::diopter {
	class type {
		friend class symbol;
		friend class scope ;
		friend class object;

		friend class dynamic_object_impl ;
		friend class constant_object_impl;

		type_impl::type_ptr _M_Impl;

		type(type_impl::type_ptr);
		type();
	public:
		using name_type = type_impl::name_type;

		template <typename... T> type(meta::meta_type<T...>&)		  ;
								 type(meta::meta_type<>&)			  ;
								 type(meta::concepts::primitive auto&);

	public:
		name_type name				   ();
		bool	  link_type			   (name_type, type&);
		
		bool	  primitive			   ();
		bool	  inner_declaration	   ();

		type	  operator[]		   (name_type);
		type	  get_inner_declaration(name_type);
		type		  super_declaration(name_type);

				  operator bool	  	   ();
	};

	template <typename... T>
	type::type(meta::meta_type<T...>& pInitType)
		: _M_Impl(std::make_shared<type_impl>(pInitType)) { }
	type::type(meta::concepts::primitive auto& pInitType)
		: _M_Impl(std::make_shared<type_impl>(pInitType)) { }
}