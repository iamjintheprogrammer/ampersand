#include "operand_impl.hpp"

namespace ampersand::diopter {
	void
		operand_declare_impl::_M_Init_Impl
			(meta::primitive_category pCategory, name_type_impl pName) {
		_M_Impl_Declare_Type   = declare_type_impl::primitive_type;
		_M_Impl_Primitive_Type = pCategory;
		_M_Impl_Name		   = pName;
	}

	void
		operand_declare_impl::_M_Init_Impl
			(name_type_impl pType, name_type_impl pName) {
		_M_Impl_Declare_Type = declare_type_impl::object;
		_M_Impl_Type		 = pType;
		_M_Impl_Name		 = pName;
	}

	void
		operand_declare_impl::_M_Init_Impl
			(name_type_impl pName) {
		_M_Impl_Declare_Type = declare_type_impl::type;
		_M_Impl_Name		 = pName;
	}


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

	operand_impl::operand_impl(name_type pType, name_type pName)
		: _M_Impl_Dynamic(pType, pName),
		  _M_Impl_Type   (category::dynamic) {}

	operand_impl::operand_impl(meta::primitive_category pType, name_type pName)
		: _M_Impl_Dynamic(pType, pName),
		  _M_Impl_Type (category::dynamic) {}

	operand_impl::operand_impl()
		: _M_Impl_Type (category::none) {}

	operand_impl::operand_impl(const operand_impl& pCopy)
		:  _M_Impl_Type (pCopy._M_Impl_Type) {
		switch (_M_Impl_Type) {
			case category::constant:
				_M_Impl_Constant = pCopy._M_Impl_Constant;
				break;
			case category::dynamic: {
				_M_Impl_Dynamic = pCopy._M_Impl_Dynamic;
				break;
			}
		}
	}

	operand_impl::category operand_impl::get_category() { 
		return _M_Impl_Type;
	}

	operand_impl::name_type operand_impl::type_name() {
		if (_M_Impl_Type != operand_type_impl::dynamic)
			return name_type{ };
		else
			return
				_M_Impl_Dynamic.type_name();
	}

	operand_impl::name_type	operand_impl::name() {
		if (_M_Impl_Type != operand_type_impl::dynamic)
			return name_type{ };
		else
			return
				_M_Impl_Dynamic.name();
	}

	operand_impl::operator bool() {
		return _M_Impl_Type != operand_type_impl::none;
	}

	operand_impl&
		operand_impl::operator=(const operand_impl& pCopy) {
			_M_Impl_Type  = pCopy._M_Impl_Type;
			switch (_M_Impl_Type) {
			case category::constant:
				_M_Impl_Constant = pCopy._M_Impl_Constant;
				break;
			case category::dynamic: {
				_M_Impl_Dynamic = pCopy._M_Impl_Dynamic;
				break;
			}
			}
			return *this;
	}
}