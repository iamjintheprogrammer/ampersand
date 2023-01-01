#include "floating_point.hpp"

namespace ampersand::poly {
	poly_object<float>::poly_object(float pValue, string_type pName)
		: _M_Name   (pName)		   ,
		  _M_Operand(pValue, pName),
		  _M_Value	(pValue)	   {
			machine::operand cur_initval(pValue);
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter		   ();
				  cur_module.push_object_create(_M_Operand, cur_initval);
				  cur_module.push_leave	       ();
	}

	poly_object<float>::poly_object(string_type pName)
		: _M_Name   (pName)			,
		  _M_Value  (value_type{})  ,
		  _M_Operand(_M_Value, pName) {
			machine::operand cur_initval(0.0f);
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter		   ();
				  cur_module.push_object_create(_M_Operand, cur_initval);
				  cur_module.push_leave	       ();
	}

	poly_object<float>::poly_object()
		: _M_Operand(value_type{}, "") {  }

	poly_object<float>::~poly_object() {
		machine::operand::object op_this("", "");
		_M_Operand.get_operand(op_this);

		if (op_this.name().empty()) {
			auto& cur_module = poly_binary::current();
				  cur_module.push_leave();
		}
		else {
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_object_delete(_M_Operand);
				  cur_module.push_leave();
		}
	}

	poly_object<double>::poly_object(double pValue, string_type pName)
		: _M_Name   (pName)		   ,
		  _M_Operand(pValue, pName),
		  _M_Value	(pValue)	   {
			machine::operand cur_initval(pValue, pName);
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter		  ();
				  cur_module.push_shallow_move(_M_Operand, cur_initval);
				  cur_module.push_leave	      ();
	}

	poly_object<double>::poly_object(string_type pName)
		: _M_Name   (pName)			,
		  _M_Value  (value_type{})  ,
		  _M_Operand(_M_Value, pName) {}

	poly_object<double>::poly_object()
		: _M_Operand(value_type{}, "") {  }

	poly_object<double>::~poly_object() {
		machine::operand::object op_this("", "");
		_M_Operand.get_operand(op_this);

		if (op_this.name().empty()) {
			auto& cur_module = poly_binary::current();
				  cur_module.push_leave();
		}
		else {
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_object_delete(_M_Operand);
				  cur_module.push_leave();
		}
	}
}