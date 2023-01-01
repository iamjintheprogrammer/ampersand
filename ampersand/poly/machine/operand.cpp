#include "operand.hpp"

namespace ampersand::poly::machine {
	operand::object::object
		(string_type pTypeName, string_type pName)
			: _M_Type(pTypeName),
			  _M_Name(pName)	{ }

	
	operand::constant::constant
		(const char* pString)
			: _M_Value    (reinterpret_cast<void*>(new char[std::strlen(pString) + 1])),
			  _M_ValueSize(std::strlen(pString) + 1),
			  _M_Type	  (constant_type::str)		 {
		std::memset(_M_Value, 0x00   , _M_ValueSize);
		std::memcpy(_M_Value, pString, _M_ValueSize);
	}

	operand::constant::constant
		(const wchar_t* pString)
			: _M_Value    (reinterpret_cast<void*>(new wchar_t[std::wcslen(pString) + 1])),
			  _M_ValueSize(std::wcslen(pString) + 2),
			  _M_Type	  (constant_type::wstr)  {
		std::memset(_M_Value, 0x00   , _M_ValueSize);
		std::memcpy(_M_Value, pString, _M_ValueSize);
	}

	operand::constant::constant(const constant& pCopy)
		: _M_Type	  (pCopy._M_Type)	  ,
		  _M_ValueSize(pCopy._M_ValueSize),
		  _M_Value	  (new std::uint8_t[pCopy._M_ValueSize]) {
		std::memcpy(_M_Value, pCopy._M_Value, pCopy._M_ValueSize);
	}

	operand::constant::constant(const constant&& pMove)
		: _M_Type	  (pMove._M_Type)	  ,
		  _M_ValueSize(pMove._M_ValueSize),
		  _M_Value	  (pMove._M_Value)	  {
		((constant&)pMove)._M_Value = nullptr;
	}

	operand::constant&
		operand::constant::operator=(const constant& pCopy) {
			_M_Type	     = pCopy._M_Type	  ;
			_M_ValueSize = pCopy._M_ValueSize;
		    _M_Value	 = new std::uint8_t[pCopy._M_ValueSize];

			std::memset(_M_Value, 0x00			, pCopy._M_ValueSize);
			std::memcpy(_M_Value, pCopy._M_Value, pCopy._M_ValueSize);
			return *this;
	}

	operand::constant&
		operand::constant::operator=(const constant&& pMove) {
			_M_Type	     = pMove._M_Type	 ;
			_M_ValueSize = pMove._M_ValueSize;
		    _M_Value	 = pMove._M_Value	 ;

			((constant&)pMove)._M_Value = nullptr;
			return *this;
	}

	// Primitive Object
	operand::primitive::primitive
		(category pCategory, string_type pName)
			: _M_Name	 (pName),
			  _M_Category(pCategory) { }

	operand::primitive::primitive
		(const char* pInitValue, string_type pName)
			: _M_Name	 (pName),
			  _M_Category(category::str) {}

	operand::primitive::primitive
		(const wchar_t* pInitValue, string_type pName)
			: _M_Name	 (pName),
			  _M_Category(category::wstr) {}

	operand::primitive::category
		operand::primitive::get_category() {
			return _M_Category;
	}

	operand::primitive::string_type
		operand::primitive::name() {
			return _M_Name;
	}

	operand::operand
		(string_type pTypeName, string_type pName)
			: _M_Category	   (category::object),
			  _M_Operand_Object(new object(pTypeName, pName)) {
	}

	operand::operand
		(primitive::category pCategory, string_type pName)
			: _M_Category		  (category::primitive),
			  _M_Operand_Primitive(new primitive(pCategory, pName)) {
	}

	operand::operand(const char* pConstant)
		: _M_Operand_Constant(new operand::constant(pConstant)),
		  _M_Category		 (category::constant){}
	
	operand::operand(const wchar_t* pConstant)
		: _M_Operand_Constant(new operand::constant(pConstant)),
		  _M_Category		 (category::constant){}


	operand::operand()
		: _M_Category	   (category::void_type),
		  _M_Operand_Object(nullptr)			{}

	operand::operand(const operand& pCopy)
		: _M_Category(pCopy._M_Category) {
		if (_M_Category == category::void_type)
			return;

		if (_M_Category == category::constant) {
			_M_Operand_Constant = new constant(*pCopy._M_Operand_Constant);
			return;
		}

		if (_M_Category == category::object) {
			_M_Operand_Object   = new object(*pCopy._M_Operand_Object);
			return;
		}

		if (_M_Category == category::primitive) {
			_M_Operand_Primitive = new primitive(*pCopy._M_Operand_Primitive);
			return;
		}
	}

	operand::operand(const operand&& pMove)
		: _M_Category	   (pMove._M_Category),
		  _M_Operand_Object(pMove._M_Operand_Object) {
		((operand&)pMove)._M_Category = category::void_type;
	}

	operand::~operand() {
		if (_M_Category == category::void_type)
			return;

		if (_M_Category == category::constant) {
			delete _M_Operand_Constant;
			return;
		}

		if (_M_Category == category::object) {
			delete _M_Operand_Object;
			return;
		}

		if (_M_Category == category::primitive) {
			delete _M_Operand_Primitive;
			return;
		}
	}

	operand::category
		operand::operand_category() {
			return _M_Category;
	}

	bool operand::get_operand(object& pObject) {
		if (_M_Category != category::object)
			return false;

		pObject = *_M_Operand_Object;
		return true;
	}

	bool operand::get_operand(constant& pConstant) {
		if (_M_Category != category::constant)
			return false;

		pConstant = *_M_Operand_Constant;
		return true;
	}

	bool operand::get_operand(primitive& pConstant) {
		if (_M_Category != category::primitive)
			return false;

		pConstant = *_M_Operand_Primitive;
		return true;
	}

	operand::object::string_type&
		operand::object::name()		 { return _M_Name; }
	operand::object::string_type&
		operand::object::type_name() { return _M_Type; }
	
	operand::constant::~constant() {
		if (!_M_Value) return;

		switch (_M_Type) {
		case __constant_type::i8:
			delete (std::int8_t*) _M_Value; break;
		case __constant_type::u8:
			delete (std::uint8_t*)_M_Value; break;

		case __constant_type::i16:
			delete (std::int16_t*) _M_Value; break;
		case __constant_type::u16:
			delete (std::uint16_t*)_M_Value; break;

		case __constant_type::i32:
			delete (std::int32_t*) _M_Value; break;
		case __constant_type::u32:
			delete (std::uint32_t*)_M_Value; break;

		case __constant_type::i64:
			delete (std::int64_t*) _M_Value; break;
		case __constant_type::u64:
			delete (std::uint64_t*)_M_Value; break;

		case __constant_type::f32:
			delete (float*) _M_Value; break;
		case __constant_type::f64:
			delete (double*)_M_Value; break;

		case __constant_type::str:
			delete (char*)   _M_Value; break;
		case __constant_type::wstr:
			delete (wchar_t*)_M_Value; break;
		}
	}

	std::string
		operand::constant::get_string_value() {
			switch (_M_Type) {
			case __constant_type::i8:
				return std::to_string(*(std::int8_t*) _M_Value);
			case __constant_type::u8:
				return std::to_string(*(std::uint8_t*)_M_Value);

			case __constant_type::i16:
				return std::to_string(*(std::int16_t*)_M_Value);
			case __constant_type::u16:
				return std::to_string(*(std::uint16_t*)_M_Value);

			case __constant_type::i32:
				return std::to_string(*(std::int32_t*) _M_Value);
			case __constant_type::u32:
				return std::to_string(*(std::uint32_t*)_M_Value);

			case __constant_type::i64:
				return std::to_string(*(std::int64_t*) _M_Value);
			case __constant_type::u64:
				return std::to_string(*(std::uint64_t*)_M_Value);

			case __constant_type::f32:
				return std::to_string(*(float*) _M_Value);
			case __constant_type::f64:
				return std::to_string(*(double*)_M_Value);

			case __constant_type::str:
				return std::string((char*)_M_Value);
			default:
				return {};
		}
	}

	std::wstring
		operand::constant::get_wstring_value() {
			switch (_M_Type) {
			case __constant_type::i8:
				return std::to_wstring(*(std::int8_t*) _M_Value);
			case __constant_type::u8:
				return std::to_wstring(*(std::uint8_t*)_M_Value);

			case __constant_type::i16:
				return std::to_wstring(*(std::int16_t*) _M_Value);
			case __constant_type::u16:
				return std::to_wstring(*(std::uint16_t*)_M_Value);

			case __constant_type::i32:
				return std::to_wstring(*(std::int32_t*) _M_Value);
			case __constant_type::u32:
				return std::to_wstring(*(std::uint32_t*)_M_Value);

			case __constant_type::i64:
				return std::to_wstring(*(std::int64_t*) _M_Value);
			case __constant_type::u64:
				return std::to_wstring(*(std::uint64_t*)_M_Value);

			case __constant_type::f32:
				return std::to_wstring(*(float*) _M_Value);
			case __constant_type::f64:
				return std::to_wstring(*(double*)_M_Value);

			case __constant_type::wstr:
				return std::wstring((wchar_t*)_M_Value);
			default:
				return {};
		}
	}

	bool
		operand::constant::get_value
			(std::int8_t& pValue) {
		if (_M_Type != __constant_type::i8)
			return false;

		pValue = *reinterpret_cast<std::int8_t*>(_M_Value);
		return true;
	}

	bool
		operand::constant::get_value
			(std::uint8_t& pValue) {
		if (_M_Type != __constant_type::u8)
			return false;

		pValue = *reinterpret_cast<std::uint8_t*>(_M_Value);
		return true;
	}

	bool
		operand::constant::get_value
			(std::int16_t& pValue) {
		if (_M_Type != __constant_type::i16)
			return false;

		pValue = *reinterpret_cast<std::int16_t*>(_M_Value);
		return true;
	}

	bool
		operand::constant::get_value
			(std::uint16_t& pValue) {
		if (_M_Type != __constant_type::u16)
			return false;

		pValue = *reinterpret_cast<std::uint16_t*>(_M_Value);
		return true;
	}

	bool
		operand::constant::get_value
			(std::int32_t& pValue) {
		if (_M_Type != __constant_type::i32)
			return false;

		pValue = *reinterpret_cast<std::int32_t*>(_M_Value);
		return true;
	}

	bool
		operand::constant::get_value
			(std::uint32_t& pValue) {
		if (_M_Type != __constant_type::u32)
			return false;

		pValue = *reinterpret_cast<std::uint32_t*>(_M_Value);
		return true;
	}

	bool
		operand::constant::get_value
			(std::int64_t& pValue) {
		if (_M_Type != __constant_type::i64)
			return false;

		pValue = *reinterpret_cast<std::int64_t*>(_M_Value);
		return true;
	}

	bool
		operand::constant::get_value
			(std::uint64_t& pValue) {
		if (_M_Type != __constant_type::u64)
			return false;

		pValue = *reinterpret_cast<std::uint64_t*>(_M_Value);
		return true;
	}

	bool
		operand::constant::get_value
			(float& pValue) {
		if (_M_Type != __constant_type::f32)
			return false;

		pValue = *reinterpret_cast<float*>(_M_Value);
		return true;
	}

	bool
		operand::constant::get_value
			(double& pValue) {
		if (_M_Type != __constant_type::f64)
			return false;

		pValue = *reinterpret_cast<double*>(_M_Value);
		return true;
	}

	bool
		operand::constant::get_value
			(std::string& pValue) {
		if (_M_Type != __constant_type::str)
			return false;

		pValue = *reinterpret_cast<char*>(_M_Value);
		return true;
	}

	bool
		operand::constant::get_value
			(std::wstring& pValue) {
		if (_M_Type != __constant_type::wstr)
			return false;

		pValue = *reinterpret_cast<wchar_t*>(_M_Value);
		return true;
	}
}