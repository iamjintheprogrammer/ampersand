#pragma once
#include <ampersand/meta/attribute.hpp>

#include <ampersand/poly/poly_object.hpp>
#include <ampersand/poly/poly_binary.hpp>

#include <ampersand/poly/machine/operand.hpp>

namespace ampersand::poly {
	template <std::integral ValueType>
	class poly_object<ValueType> {
		template <typename... AnyType>
		friend class poly_object;

		using __value_type  = ValueType;
		using __string_type = std::string;

		__value_type     _M_Value  ;
		__string_type    _M_Name   ;
		machine::operand _M_Operand;
	
	public:
		using value_type  = __value_type ;
		using string_type = __string_type;

	public:
		 poly_object(value_type, string_type);
		 poly_object(string_type);
	 	 poly_object();
	    ~poly_object();

	public:
												 value_type				 operator* ();
		template <std::floating_point FloatType> poly_object<ValueType>& operator= (poly_object<FloatType>&)    ;
		template <std::floating_point FloatType> poly_object<ValueType>& operator= (poly_object<FloatType>&&)   ;
		template <std::integral IntegralType>    poly_object<ValueType>& operator= (poly_object<IntegralType>&) ;
		template <std::integral IntegralType>    poly_object<ValueType>& operator= (poly_object<IntegralType>&&);

		template <typename RhsType>				 auto	   				 operator+ (RhsType&&);
		template <typename RhsType>				 poly_object<ValueType>& operator+=(RhsType&&);
		template <typename RhsType>				 auto					 operator- (RhsType&&);
		template <typename RhsType>				 poly_object<ValueType>& operator-=(RhsType&&);
		template <typename RhsType>				 auto					 operator* (RhsType&&);
		template <typename RhsType>				 poly_object<ValueType>& operator*=(RhsType&&);
		template <typename RhsType>				 auto					 operator/ (RhsType&&);
		template <typename RhsType>				 poly_object<ValueType>& operator/=(RhsType&&);
		
	};

	template <std::integral ValueType>
	template <std::floating_point FloatType>
	poly_object<ValueType>&
		poly_object<ValueType>::operator= (poly_object<FloatType>& pCopy) {
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter		  ();
				  cur_module.push_shallow_move(_M_Operand, pCopy._M_Operand);
				  cur_module.push_leave	      ();
			return *this;
	}

	template <std::integral ValueType>
	template <std::floating_point FloatType>
	poly_object<ValueType>&
		poly_object<ValueType>::operator= (poly_object<FloatType>&& pMove) {
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter		  ();
				  cur_module.push_move		  (_M_Operand, pMove._M_Operand);
				  cur_module.push_leave	      ();
			return *this;
	}

	template <std::integral ValueType>
	template <std::integral IntegralType>
	poly_object<ValueType>&
		poly_object<ValueType>::operator= (poly_object<IntegralType>& pCopy) {
			_M_Value = *pCopy;
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter		  ();
				  cur_module.push_shallow_move(_M_Operand, pCopy._M_Operand);
				  cur_module.push_leave	      ();
			return *this;
	}

	template <std::integral ValueType>
	template <std::integral IntegralType>
	poly_object<ValueType>&
		poly_object<ValueType>::operator= (poly_object<IntegralType>&& pMove) {
			_M_Value = *pMove;
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter		  ();
				  cur_module.push_move		  (_M_Operand, pMove._M_Operand);
				  cur_module.push_leave	      ();
			return *this;
	}

	template <std::integral ValueType>
	typename poly_object<ValueType>::value_type
		poly_object<ValueType>::operator* () {
			return _M_Value;
	}
	
	template <std::integral ValueType>
	template <typename RhsType>
	auto
		poly_object<ValueType>::operator+(RhsType&& pRhsObject) {
		static_assert
			(std::is_integral_v
				<typename std::remove_reference_t<RhsType>::value_type> || 
			 std::is_floating_point_v<typename std::remove_reference_t<RhsType>::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();

			if constexpr 
				(std::is_floating_point_v
					<typename std::remove_reference_t<RhsType>::value_type>) {
						machine::operand op_return(*pRhsObject + _M_Value, "");
						cur_module.push_primitive_operator
							(machine::instruction_verb::op_add,
								op_return, _M_Operand, pRhsObject._M_Operand);
			
						return 
							std::remove_reference_t<RhsType>{ *pRhsObject + _M_Value, ""};
			}

			if constexpr
				(std::is_integral_v
					<typename std::remove_reference_t<RhsType>::value_type>) {
						machine::operand op_return(*pRhsObject + _M_Value, "");
						cur_module.push_primitive_operator
							(machine::instruction_verb::op_add,
								op_return, _M_Operand, pRhsObject._M_Operand);
			
						return poly_object<ValueType>{ *pRhsObject + _M_Value, ""};
			}
	}

	template <std::integral ValueType>
	template <typename RhsType>
	poly_object<ValueType>&
		poly_object<ValueType>::operator+=(RhsType&& pRhsObject) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_primitive_operator
						(machine::instruction_verb::op_addeq,
							_M_Operand, _M_Operand, pRhsObject._M_Operand);
				  cur_module.push_leave();

			return *this;
	}

	template <std::integral ValueType>
	template <typename RhsType>
	auto
		poly_object<ValueType>::operator-(RhsType&& pRhsObject) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");
		auto& cur_module = poly_binary::current();
			  cur_module.push_enter();

		if constexpr 
			(std::is_floating_point_v<typename RhsType::value_type>) {
				machine::operand op_return(*pRhsObject + _M_Value, "");
				cur_module.push_primitive_operator
					(machine::instruction_verb::op_sub,
						op_return, _M_Operand, pRhsObject._M_Operand);
			
				return RhsType{ *pRhsObject + _M_Value, ""};
		}

		if constexpr
			(std::is_integral_v<typename RhsType::value_type>) {
				machine::operand op_return(*pRhsObject + _M_Value, "");
				cur_module.push_primitive_operator
					(machine::instruction_verb::op_sub,
						op_return, _M_Operand, pRhsObject._M_Operand);
			
				return poly_object<ValueType>{ *pRhsObject + _M_Value, ""};
		}
	}

	template <std::integral ValueType>
	template <typename RhsType>
	poly_object<ValueType>&
		poly_object<ValueType>::operator-=(RhsType&& pRhsObject) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_primitive_operator
						(machine::instruction_verb::op_subeq,
							_M_Operand, _M_Operand, pRhsObject._M_Operand);
				  cur_module.push_leave();

			return *this;
	}

	template <std::integral ValueType>
	template <typename RhsType>
	auto
		poly_object<ValueType>::operator*(RhsType&& pRhsObject) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");
		auto& cur_module = poly_binary::current();
			  cur_module.push_enter();

		if constexpr 
			(std::is_floating_point_v<typename RhsType::value_type>) {
				machine::operand op_return(*pRhsObject + _M_Value, "");
				cur_module.push_primitive_operator
					(machine::instruction_verb::op_mul,
						op_return, _M_Operand, pRhsObject._M_Operand);
			
				return RhsType{ *pRhsObject + _M_Value, ""};
		}

		if constexpr
			(std::is_integral_v<typename RhsType::value_type>) {
				machine::operand op_return(*pRhsObject + _M_Value, "");
				cur_module.push_primitive_operator
					(machine::instruction_verb::op_mul,
						op_return, _M_Operand, pRhsObject._M_Operand);
			
				return poly_object<ValueType>{ *pRhsObject + _M_Value, ""};
		}
	}

	template <std::integral ValueType>
	template <typename RhsType>
	poly_object<ValueType>&
		poly_object<ValueType>::operator*=(RhsType&& pRhsObject) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_primitive_operator
						(machine::instruction_verb::op_muleq,
							_M_Operand, _M_Operand, pRhsObject._M_Operand);
				  cur_module.push_leave();

			return *this;
	}

	template <std::integral ValueType>
	template <typename RhsType>
	auto
		poly_object<ValueType>::operator/(RhsType&& pRhsObject) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");
		auto& cur_module = poly_binary::current();
			  cur_module.push_enter();

		if constexpr 
			(std::is_floating_point_v<typename RhsType::value_type>) {
				machine::operand op_return(*pRhsObject + _M_Value, "");
				cur_module.push_primitive_operator
					(machine::instruction_verb::op_div,
						op_return, _M_Operand, pRhsObject._M_Operand);
			
				return RhsType{ *pRhsObject + _M_Value, ""};
		}

		if constexpr
			(std::is_integral_v<typename RhsType::value_type>) {
				machine::operand op_return(*pRhsObject + _M_Value, "");
				cur_module.push_primitive_operator
					(machine::instruction_verb::op_div,
						op_return, _M_Operand, pRhsObject._M_Operand);
			
				return poly_object<ValueType>{ *pRhsObject + _M_Value, ""};
		}
	}

	template <std::integral ValueType>
	template <typename RhsType>
	poly_object<ValueType>&
		poly_object<ValueType>::operator/=(RhsType&& pRhsObject) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_primitive_operator
						(machine::instruction_verb::op_diveq,
							_M_Operand, _M_Operand, pRhsObject._M_Operand);
				  cur_module.push_leave();

			return *this;
	}

	template <std::integral ValueType>
	poly_object<ValueType>::poly_object(value_type pValue, string_type pName)
		: _M_Name   (pName)		   ,
		  _M_Operand(pValue, pName),
		  _M_Value	(pValue)	   {
			machine::operand cur_initval(pValue);
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter		   ();
				  cur_module.push_object_create(_M_Operand, cur_initval);
				  cur_module.push_leave	       ();
	}

	template <std::integral ValueType>
	poly_object<ValueType>::poly_object(string_type pName)
		: _M_Name   (pName)			,
		  _M_Value  (ValueType{})   ,
		  _M_Operand(_M_Value, pName) {
			machine::operand cur_initval(0);
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter		   ();
				  cur_module.push_object_create(_M_Operand, cur_initval);
				  cur_module.push_leave	       ();
	}

	template <std::integral ValueType>
	poly_object<ValueType>::poly_object()
		: _M_Operand(ValueType{}, "") {  }

	template <std::integral ValueType>
	poly_object<ValueType>::~poly_object() {
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

	template <std::integral ValueType, typename StringType>
	poly_object(ValueType, StringType) -> poly_object<ValueType>;
}