#pragma once
#include <ampersand/meta.hpp>

namespace ampersand::diopter {
	class operand_declare_impl {
		using		  name_type_impl = std::string;
		enum class declare_type_impl { type, primitive_type, object };
		declare_type_impl		 _M_Impl_Declare_Type  ;
		meta::primitive_category _M_Impl_Primitive_Type;
		name_type_impl			 _M_Impl_Type,
								 _M_Impl_Name;
		
		void _M_Init_Impl(meta::primitive_category, name_type_impl);
		void _M_Init_Impl(name_type_impl		  , name_type_impl);
		void _M_Init_Impl(name_type_impl);
	public:
		operand_declare_impl(meta::concepts::meta_object auto&);
		operand_declare_impl(meta::concepts::meta_type   auto&);

		
	};

	class operand_dynamic_impl {
		using name_type_impl = std::string;
		name_type_impl _M_Impl_Type,
					   _M_Impl_Name;

		bool					 _M_Impl_Primitive;
		meta::primitive_category _M_Impl_Primitive_Category;
	public:
		using name_type = name_type_impl;
		operand_dynamic_impl(name_type, name_type);
		operand_dynamic_impl(meta::primitive_category, name_type);
		operand_dynamic_impl() = default;
		
		bool					 primitive		   ();
		meta::primitive_category primitive_category();

		name_type				 type_name();
		name_type				 name	  ();
	};

	class operand_constant_impl   {
		union constant_union_impl {
			int8_t  i8 ; uint8_t  u8 ;
			int16_t i16; uint16_t u16;
			int32_t i32; uint32_t u32;
			int64_t i64; uint64_t u64;
			float   f32; double   f64;
		} _M_Impl_Union    ;

		enum class constant_type_impl {
			i8 , u8 ,
			i16, u16,
			i32, u32,
			i64, u64,
			f32, f64,

			any
		};

		constant_type_impl _M_Impl_Type;
	public:
		using constant_type = constant_type_impl;

		template <std::floating_point T> operand_constant_impl(T);
		template <std::integral T>		 operand_constant_impl(T);
										 operand_constant_impl( ) = default;

		constant_type get_type_of();

		bool		  get_value(int8_t  &);
		bool		  get_value(uint8_t &);

		bool		  get_value(int16_t &);
		bool		  get_value(uint16_t&);

		bool		  get_value(int32_t &);
		bool		  get_value(uint32_t&);

		bool		  get_value(int64_t &);
		bool		  get_value(uint64_t&);

		bool		  get_value(float &);
		bool		  get_value(double&);
	};

	class operand_impl {
		enum class operand_category_impl  { constant, dynamic, declare, none };

		operand_category_impl _M_Impl_Type	  ;
		operand_constant_impl _M_Impl_Constant;
		operand_dynamic_impl  _M_Impl_Dynamic ;
		operand_declare_impl  _M_Impl_Declare ;
				
	public:
		using name_type = operand_dynamic_impl::name_type;
		using category  = operand_category_impl;
										 operand_impl();
										 operand_impl(const operand_impl&);
										 operand_impl(name_type				  , name_type);
										 operand_impl(meta::primitive_category, name_type);
										 operand_impl(meta::concepts::meta_object auto&);
										 operand_impl(meta::concepts::meta_type   auto&);
		template <std::floating_point T> operand_impl(T);
		template <std::integral T>		 operand_impl(T);

		template <std::floating_point T> bool get_value(T&); // Only valid if _M_Impl_Type is category::constant
		template <std::integral T>		 bool get_value(T&); // Only valid if _M_Impl_Type is category::constant

		category  get_category();
		name_type type_name   (); // Only valid if _M_Impl_Type is category::dynamic or category::declare
		name_type	   name   (); // Only valid if _M_Impl_Type is category::dynamic or category::declare
					  operator bool();
		operand_impl& operator=	   (const operand_impl&);
	};

	operand_declare_impl::operand_declare_impl
		(meta::concepts::meta_object auto& pMetaObject) {
		_M_Init_Impl(pMetaObject.type_of().type_id(), pMetaObject.name());
	}

	operand_declare_impl::operand_declare_impl
		(meta::concepts::meta_type auto& pMetaType) {
			_M_Init_Impl(pMetaType.type_id());
	}

	template <std::floating_point T>
	operand_constant_impl::operand_constant_impl(T pValue) {
		if constexpr (std::is_same_v<T, float>) {
			_M_Impl_Type = constant_type_impl::f32;
			_M_Impl_Union.f32 = pValue;
		}
		else if constexpr (std::is_same_v<T, double>) {
			_M_Impl_Type	  = constant_type::f64;
			_M_Impl_Union.f64 = pValue;
		}
	}
	template <std::integral T>
	operand_constant_impl::operand_constant_impl(T pValue) {
		if constexpr (std::is_same_v<T, int8_t>) {
			_M_Impl_Type = constant_type_impl::f32;
			_M_Impl_Union.f32 = pValue;
		}
		else if constexpr (std::is_same_v<T, uint8_t>) {
			_M_Impl_Type	  = constant_type::f64;
			_M_Impl_Union.f64 = pValue;
		}

		else if constexpr (std::is_same_v<T, int16_t>) {
			_M_Impl_Type	  = constant_type::i16;
			_M_Impl_Union.f64 = pValue;
		}
		else if constexpr (std::is_same_v<T, uint16_t>) {
			_M_Impl_Type	  = constant_type::u16;
			_M_Impl_Union.f64 = pValue;
		}

		else if constexpr (std::is_same_v<T, int32_t>) {
			_M_Impl_Type	  = constant_type::i32;
			_M_Impl_Union.f64 = pValue;
		}
		else if constexpr (std::is_same_v<T, uint32_t>) {
			_M_Impl_Type	  = constant_type::u32;
			_M_Impl_Union.f64 = pValue;
		}

		else if constexpr (std::is_same_v<T, int64_t>) {
			_M_Impl_Type	  = constant_type::i64;
			_M_Impl_Union.f64 = pValue;
		}
		else if constexpr (std::is_same_v<T, uint64_t>) {
			_M_Impl_Type	  = constant_type::u64;
			_M_Impl_Union.f64 = pValue;
		}
	}

	template <std::floating_point T>
	operand_impl::operand_impl(T pValue)
		: _M_Impl_Constant(pValue),
		  _M_Impl_Type    (category::constant) {}
	template <std::integral T>
	operand_impl::operand_impl(T pValue) 
		: _M_Impl_Constant(pValue),
		  _M_Impl_Type    (category::constant) {}

	operand_impl::operand_impl
		(meta::concepts::meta_object auto& pMetaObject)
			: _M_Impl_Declare(pMetaObject),
			  _M_Impl_Type   (category::declare) {}
	operand_impl::operand_impl(meta::concepts::meta_type   auto&);

	template <std::floating_point T>
	bool operand_impl::get_value(T& pValue) {
		if (_M_Impl_Type != operand_type_impl::constant)
			return false;

		return
			_M_Impl_Constant.get_value(pValue);
	}
	template <std::integral T>
	bool operand_impl::get_value(T& pValue) {
		if (_M_Impl_Type != operand_type_impl::constant)
			return false;

		return
			_M_Impl_Constant.get_value(pValue);
	}
}