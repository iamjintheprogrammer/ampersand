#include "operation_impl.hpp"

namespace ampersand::diopter {
	operand_dynamic_impl::operand_dynamic_impl
		(name_type pType, name_type pName)
			: _M_Impl_Type(pType),
			  _M_Impl_Name(pName) {}

	operand_dynamic_impl::name_type
		operand_dynamic_impl::type_name() { return _M_Impl_Type; }

	operand_dynamic_impl::name_type
		operand_dynamic_impl::name()	  { return _M_Impl_Name; }

	operand_dynamic_impl::operand_dynamic_impl
		(meta::primitive_category pCategory, name_type pName)
			: _M_Impl_Primitive			(true)	   ,
			  _M_Impl_Primitive_Category(pCategory),
			  _M_Impl_Name				(pName)	   {  }

	bool operand_dynamic_impl::primitive() { return _M_Impl_Primitive; }
	meta::primitive_category
		operand_dynamic_impl::primitive_category() {
			return _M_Impl_Primitive_Category;
	}

	operand_constant_impl::constant_type
		operand_constant_impl::get_type_of() { return _M_Impl_Type; }

	bool operand_constant_impl::get_value(int8_t& pValue) {
		if (_M_Impl_Type != constant_type_impl::i8)
			return false;
		
		pValue = _M_Impl_Union.i8;
		return true;
	}
	bool operand_constant_impl::get_value(uint8_t& pValue) {
		if (_M_Impl_Type != constant_type_impl::u8)
			return false;
		
		pValue = _M_Impl_Union.u8;
		return true;
	}

	bool operand_constant_impl::get_value(int16_t& pValue) {
		if (_M_Impl_Type != constant_type_impl::i16)
			return false;

		pValue = _M_Impl_Union.i16;
		return true;
	}

	bool operand_constant_impl::get_value(uint16_t& pValue) {
		if (_M_Impl_Type != constant_type_impl::u16)
			return false;

		pValue = _M_Impl_Union.u16;
		return true;
	}

	bool operand_constant_impl::get_value(int32_t& pValue) {
		if (_M_Impl_Type != constant_type_impl::i32)
			return false;

		pValue = _M_Impl_Union.i32;
		return true;
	}

	bool operand_constant_impl::get_value(uint32_t& pValue) {
		if (_M_Impl_Type != constant_type_impl::u32)
			return false;

		pValue = _M_Impl_Union.u32;
		return true;
	}

	bool operand_constant_impl::get_value(int64_t& pValue) {
		if (_M_Impl_Type != constant_type_impl::i64)
			return false;

		pValue = _M_Impl_Union.i64;
		return true;
	}

	bool operand_constant_impl::get_value(uint64_t& pValue) {
		if (_M_Impl_Type != constant_type_impl::u64)
			return false;

		pValue = _M_Impl_Union.u64;
		return true;
	}

	bool operand_constant_impl::get_value(float& pValue) {
		if (_M_Impl_Type != constant_type_impl::f32)
			return false;

		pValue = _M_Impl_Union.f32;
		return true;
	}

	bool operand_constant_impl::get_value(double& pValue) {
		if (_M_Impl_Type != constant_type_impl::f64)
			return false;

		pValue = _M_Impl_Union.f64;
		return true;
	}

	operand_impl::operand_union_impl::operand_union_impl
		(operand_dynamic_impl::name_type pType, operand_dynamic_impl::name_type pName)
			: u_dynamic(pType, pName) {}

	operand_impl::operand_union_impl::operand_union_impl
		(meta::primitive_category pType, operand_dynamic_impl::name_type pName)
			: u_dynamic(pType, pName) {}

	operand_impl::operand_union_impl::~operand_union_impl() {}

	operand_impl::operand_impl(name_type pType, name_type pName)
		: _M_Impl_Union(pType, pName) {}

	operand_impl::operand_impl(meta::primitive_category pType, name_type pName)
		: _M_Impl_Union(pType, pName) {}

	operand_impl::category operand_impl::get_category() { 
		return _M_Impl_Type;
	}

	operand_impl::name_type operand_impl::type_name() {
		if (_M_Impl_Type != operand_type_impl::dynamic)
			return name_type{ };
		else
			return
				_M_Impl_Union.u_dynamic.type_name();
	}

	operand_impl::name_type	operand_impl::name() {
		if (_M_Impl_Type != operand_type_impl::dynamic)
			return name_type{ };
		else
			return
				_M_Impl_Union.u_dynamic.name();
	}

	operand_impl::operator bool() {
		return _M_Impl_Type != operand_type_impl::none;
	}
}