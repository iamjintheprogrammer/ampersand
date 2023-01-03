#pragma once
#include <string>
#include <unordered_map>

namespace ampersand::diopter {
	struct		   primitive_type_impl {
		enum class primitive_category {
			i8 , u8 ,
			i16, u16,
			i32, u32,
			i64, u64,

			f32, f64,
			any
		};

		primitive_category category;
		primitive_type_impl(primitive_category);
	};

	struct complex_type_impl {
		std::unordered_map<std::string, struct type_impl*> table;
		std::string										   name ;
		complex_type_impl() = default;

		void push_subtype_impl(std::string, std::string, complex_type_impl&);
		void push_subtype_impl(std::string, primitive_type_impl&);
		void pop_subtype_impl (std::string);
	};

	struct		   type_impl     {
		enum class type_category { complex, primitive };
		type_category category;
		union u_type_impl {
			complex_type_impl   u_complex  ;
			primitive_type_impl u_primitive;

			u_type_impl() 
				: u_primitive
					(primitive_type_impl::primitive_category::any)
						{  }

			u_type_impl (complex_type_impl&   pInit) : u_complex  (pInit) {}
			u_type_impl (primitive_type_impl& pInit) : u_primitive(pInit) {}
			~u_type_impl()												  {}
		} u_type;

		type_impl(complex_type_impl&)  ;
		type_impl(primitive_type_impl&);
		
		type_impl();
		type_impl(const type_impl&);
	};
}