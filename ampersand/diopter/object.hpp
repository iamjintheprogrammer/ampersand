#pragma once
#include <ampersand/diopter/symbol.hpp>
#include <ampersand/diopter/type.hpp>

namespace ampersand::diopter {
	class dynamic_object_impl {
		type			_M_Type;
		type::name_type _M_Name;
	public:
		using  name_type = type::name_type;
		 dynamic_object_impl(name_type, type&);
		~dynamic_object_impl();

		type	  type_of();
		name_type name	 ();
	};

	class constant_object_impl {
		type			_M_Type;
		type::name_type _M_Name;
	public:
		using  name_type = type::name_type;
		 constant_object_impl(name_type, type&);
		~constant_object_impl();

		type	  type_of();
		name_type name	 ();
	};

	class object {
		friend class stack;
		friend class scope;

		enum class      category_impl { dynamic, constant, none };
		struct     uninitialized_impl {};

		union _M_Object_Impl {
			uninitialized_impl	 u_uninit  ;
			constant_object_impl u_constant;
			dynamic_object_impl  u_dynamic ;
			
			 _M_Object_Impl();
			~_M_Object_Impl();
		}			  _M_Impl_Union;
		category_impl _M_Impl_Category;

		object();
	public:
		using category  = category_impl;
		using name_type = type::name_type;

		object(category, name_type, type&);
		object(const object&) ;
		object	    (object&&);

		type      type_of	  ();
		name_type name		  ();
		category  get_category();
				 operator bool();
	};
}