#pragma once
#include <ampersand/diopter/engine/type.hpp>

namespace ampersand::diopter {
	struct none_object_impl		 {};
	struct any_object_impl		 {};
	struct primitive_object_impl {
		union {
			int8_t  i8 ; uint8_t  u8;
			int16_t i16; uint16_t u16;
			int32_t i32; uint32_t u32;
			int64_t i64; uint64_t u64;
			float   f32; double   f64;

			any_object_impl any;
		};

		primitive_object_impl(type::primitive&);
	};

	struct complex_object_impl {
		using table_type = std::unordered_map<type::string_type, struct object_impl*>;
			  table_type table;
		
		complex_object_impl(type::complex&);
	};

	struct object_impl {
		type&			  object_type;
		type::string_type name;

		union u_object_impl {
			primitive_object_impl u_primitive;
			complex_object_impl   u_complex  ;
			none_object_impl	  u_none	 ;

			 u_object_impl();
			~u_object_impl();
		}						  u_object	 ;

		object_impl(type&, type::string_type);
		object_impl(type&);
	};
}