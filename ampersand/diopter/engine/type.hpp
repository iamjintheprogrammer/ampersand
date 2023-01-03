#pragma once
#include <ampersand/diopter/engine/type_impl.hpp>

namespace ampersand::diopter {
	class type {
		type_impl _M_Impl;
		type(type_impl&);
	public:
		using category	  = type_impl::type_category;
		using string_type = std::string;

		using primitive = primitive_type_impl;
		class complex {
			friend class type;
			complex_type_impl* _M_Impl;
			complex(complex_type_impl&);

		public:
			class subtype {
				complex_type_impl::table_type::iterator _M_Base;
				complex_type_impl&						_M_Impl;
			public:
				subtype(complex&);

				type::string_type name	  ();
				type			  get_type();

				subtype& operator++()   ;
				subtype  operator++(int);
						 operator bool();
			};

		public:
			complex();

			void push_subtype(string_type, type&);
			void pop_subtype (string_type);
			type find_subtype(string_type);
		};

	public:
		type();
		type(string_type);
		type(primitive);

		category type_category();
		bool	 get_implemented_type(complex&)  ;
		bool	 get_implemented_type(primitive&);
	};
}