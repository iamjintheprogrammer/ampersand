#include "type.hpp"

namespace ampersand::diopter {
	type::complex::complex()	   : _M_Impl(nullptr) {  }
	type::complex::complex
		(complex_type_impl& pInit) : _M_Impl(&pInit)  {  }

	void
		type::complex::push_subtype
			(string_type pName, type& pType) {
		if(pType.type_category() == category::primitive)
			_M_Impl->push_subtype_impl
				(pName, pType._M_Impl.u_type.u_primitive);
		else
			_M_Impl->push_subtype_impl
				(pName, pType._M_Impl.u_type.u_complex);
	}

	void
		type::complex::pop_subtype
			(string_type pName) { _M_Impl->pop_subtype_impl(pName); }

	type
		type::complex::find_subtype
			(string_type pName) {
		auto it_find = _M_Impl->table.find(pName);
		return
			(it_find == _M_Impl->table.end())
				? type()
				: type(*(*it_find).second);
	}

	type::type()				    : _M_Impl()			 {}
	type::type(string_type pName)   : _M_Impl(pName)     {}
	type::type(primitive pCategory) : _M_Impl(pCategory) {}
	type::type(type_impl& pImpl)	: _M_Impl(pImpl)	 {}

	type::category type::type_category() { return _M_Impl.category; }
	bool
		type::get_implemented_type
			(complex& pComplex) {
		if (_M_Impl.category != category::complex)
			return false;
		else {
			pComplex = complex(_M_Impl.u_type.u_complex);
			return true;
		}
	}

	bool
		type::get_implemented_type
			(primitive& pPrimitive) {
		if (_M_Impl.category != category::primitive)
			return false;
		else {
			pPrimitive = primitive(_M_Impl.u_type.u_primitive);
			return true;
		}
	}

	type::complex::subtype::subtype
		(complex& pImpl)
			: _M_Impl(*pImpl._M_Impl),
			  _M_Base( pImpl._M_Impl->table.begin()) {  }

	type::string_type
		type::complex::subtype::name() {
			if(_M_Base == _M_Impl.table.end())
				return type::string_type();
			else
				(*_M_Base).first;
	}

	type type::complex::subtype::get_type() {
		if (_M_Base == _M_Impl.table.end())
			return type();
		else
			type(*(*_M_Base).second);
	}

	type::complex::subtype&
		type::complex::subtype::operator++() {
			if(_M_Base == _M_Impl.table.end()) return *this;

			++_M_Base;
			return *this;
	}

	type::complex::subtype
		type::complex::subtype::operator++(int) {
			if(_M_Base == _M_Impl.table.end()) return *this;

			++_M_Base;
			return *this;
	}

	type::complex::subtype::operator bool() {
		return _M_Base != _M_Impl.table.end();
	}
}