#pragma once
#include <ampersand/diopter/engine/type_impl.hpp>

namespace ampersand::diopter {
	class type {
		type_impl _M_Impl;
		type(type_impl&);
	public:
		using category	  = type_impl::type_category;
		using string_type = std::string;

		class primitive {
			primitive_type_impl* _M_Impl;
			primitive(primitive_type_impl&);
		public:
			using primitive_category = primitive_type_impl::primitive_category;

			primitive_category category();
		};

		class complex {
			complex_type_impl* _M_Impl;
			complex(complex_type_impl&);

		public:
			void  push_subtype(string_type, type&);
			void  pop_subtype (string_type);
			type* find_subtype(string_type);
		};

	public:
		type(category);

		string_type& type_name    ();
		category	 type_category();

		bool		 get_implemented_type(complex&)  ;
		bool		 get_implemented_type(primitive&);
	};
}