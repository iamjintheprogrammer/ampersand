#pragma once
#include <string>
#include <unordered_map>

namespace ampersand::diopter {
	struct			none_type_impl {};
	enum class primitive_type_impl {
		i8 , u8 ,
		i16, u16,
		i32, u32,
		i64, u64,

		f32, f64,
		any
	};

	struct complex_type_impl {
		using table_type = std::unordered_map<std::string, struct type_impl*>;
		table_type  table;
		std::string name ;
		 complex_type_impl(std::string);
		~complex_type_impl();

		void push_subtype_impl(std::string, complex_type_impl&);
		void push_subtype_impl(std::string, primitive_type_impl&);
		void pop_subtype_impl (std::string);
	};

	struct		   type_impl     {
		enum class type_category { complex, primitive, none };
		type_category category;
		union u_type_impl {
			complex_type_impl	u_complex  ;
			primitive_type_impl u_primitive;
			none_type_impl		u_none	   ;

			 u_type_impl();						// Init to "none" type.
			 u_type_impl(std::string);			// Init to "complex" type
			 u_type_impl(primitive_type_impl) ; // Init to "primitive" type
			 u_type_impl(complex_type_impl&)  ; // Init to "complex" type from existing type object.
			~u_type_impl();
		} u_type;

		type_impl();					 // Invoke u_type_impl::u_type_impl()
		type_impl(std::string);			 // Invoke u_type_impl::u_type_impl(std::string)
		type_impl(primitive_type_impl) ; // Invoke u_type_impl::u_type_impl(primitive_category)
		type_impl(complex_type_impl&)  ; // Invoke u_type_impl::u_type_impl(complex_type_impl&)
		
		type_impl(const type_impl&);
	};
}