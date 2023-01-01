#pragma once
#include <ampersand/meta/attribute.hpp>

#include <ampersand/poly/poly_object.hpp>
#include <ampersand/poly/poly_binary.hpp>

#include <ampersand/poly/machine/operand.hpp>

namespace ampersand::poly {
	template <>
	class poly_object<float> {
		template <typename... AnyType>
		friend class poly_object;

		using __value_type  = float;
		using __string_type = std::string;

		__value_type     _M_Value  ;
		__string_type    _M_Name   ;
		machine::operand _M_Operand;
	
	public:
		using value_type  = __value_type ;
		using string_type = __string_type;

	public:
		 poly_object(float, string_type);
		 poly_object(string_type);
		 poly_object();
		~poly_object();

	public:
									value_type			operator* ();
		template <typename RhsType> poly_object<float>& operator= (RhsType&&);
		template <typename RhsType> auto	   			operator+ (RhsType&&);
		template <typename RhsType> poly_object<float>& operator+=(RhsType&&);
		template <typename RhsType> auto				operator- (RhsType&&);
		template <typename RhsType> poly_object<float>& operator-=(RhsType&&);
		template <typename RhsType> auto				operator* (RhsType&&);
		template <typename RhsType> poly_object<float>& operator*=(RhsType&&);
		template <typename RhsType> auto				operator/ (RhsType&&);
		template <typename RhsType> poly_object<float>& operator/=(RhsType&&);
	};

	template <>
	class poly_object<double> {
		template <typename... AnyType>
		friend class poly_object;

		using __value_type  = double;
		using __string_type = std::string;

		__value_type     _M_Value  ;
		__string_type    _M_Name   ;
		machine::operand _M_Operand;
	
	public:
		using value_type  = __value_type ;
		using string_type = __string_type;

	public:
		 poly_object(double, string_type);
		 poly_object(string_type);
		 poly_object();
		~poly_object();

	public:
									value_type			 operator* ();
		template <typename RhsType> poly_object<double>& operator= (RhsType&&);
		template <typename RhsType> auto	   			 operator+ (RhsType&&);
		template <typename RhsType> poly_object<double>& operator+=(RhsType&&);
		template <typename RhsType> auto				 operator- (RhsType&&);
		template <typename RhsType> poly_object<double>& operator-=(RhsType&&);
		template <typename RhsType> auto				 operator* (RhsType&&);
		template <typename RhsType> poly_object<double>& operator*=(RhsType&&);
		template <typename RhsType> auto				 operator/ (RhsType&&);
		template <typename RhsType> poly_object<double>& operator/=(RhsType&&);
	};

	template <typename RhsType>
	poly_object<float>&
		poly_object<float>::operator= (RhsType&& pCopy) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");

			auto& cur_module = poly_binary::current();
				  cur_module.push_enter		  ();
				  cur_module.push_shallow_move(_M_Operand, pCopy._M_Operand);
				  cur_module.push_leave	      ();
			return *this;
	}

	typename poly_object<float>::value_type
		poly_object<float>::operator* () {
			return _M_Value;
	}
	
	template <typename RhsType>
	auto
		poly_object<float>::operator+(RhsType&& pRhsObject) {
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
						(machine::instruction_verb::op_add,
							op_return, _M_Operand, pRhsObject._M_Operand);
			
					return RhsType{ *pRhsObject + _M_Value, ""};
		}

			if constexpr
				(std::is_integral_v<typename RhsType::value_type>) {
					machine::operand op_return(*pRhsObject + _M_Value, "");
					cur_module.push_primitive_operator
						(machine::instruction_verb::op_add,
							op_return, _M_Operand, pRhsObject._M_Operand);
			
					return poly_object<float>{ *pRhsObject + _M_Value, ""};
		}
	}

	template <typename RhsType>
	poly_object<float>&
		poly_object<float>::operator+=(RhsType&& pRhsObject) {
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

	template <typename RhsType>
	auto
		poly_object<float>::operator-(RhsType&& pRhsObject) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");

		machine::operand op_return(*pRhsObject + _M_Value, "");
		auto& cur_module = poly_binary::current();
			  cur_module.push_enter();
			  cur_module.push_primitive_operator
					(machine::instruction_verb::op_sub,
						op_return, _M_Operand, pRhsObject._M_Operand);
			
		return poly_object<float>{ *pRhsObject + _M_Value, ""};
	}

	template <typename RhsType>
	poly_object<float>&
		poly_object<float>::operator-=(RhsType&& pRhsObject) {
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

	template <typename RhsType>
	auto
		poly_object<float>::operator*(RhsType&& pRhsObject) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");

		machine::operand op_return(*pRhsObject + _M_Value, "");
		auto& cur_module = poly_binary::current();
			  cur_module.push_enter();
			  cur_module.push_primitive_operator
					(machine::instruction_verb::op_mul,
						op_return, _M_Operand, pRhsObject._M_Operand);
			
		return poly_object<float>{ *pRhsObject + _M_Value, ""};
	}

	template <typename RhsType>
	poly_object<float>&
		poly_object<float>::operator*=(RhsType&& pRhsObject) {
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

	template <typename RhsType>
	auto
		poly_object<float>::operator/(RhsType&& pRhsObject) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");

		machine::operand op_return(*pRhsObject + _M_Value, "");
		auto& cur_module = poly_binary::current();
			  cur_module.push_enter();
			  cur_module.push_primitive_operator
					(machine::instruction_verb::op_div,
						op_return, _M_Operand, pRhsObject._M_Operand);
			
		return poly_object<float>{ *pRhsObject + _M_Value, ""};
	}

	template <typename RhsType>
	poly_object<float>&
		poly_object<float>::operator/=(RhsType&& pRhsObject) {
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

	

	//Double
	template <typename RhsType>
	poly_object<double>&
		poly_object<double>::operator= (RhsType&& pCopy) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");

			auto& cur_module = poly_binary::current();
				  cur_module.push_enter		  ();
				  cur_module.push_shallow_move(_M_Operand, pCopy._M_Operand);
				  cur_module.push_leave	      ();
			return *this;
	}

	typename poly_object<double>::value_type
		poly_object<double>::operator* () {
			return _M_Value;
	}
	
	template <typename RhsType>
	auto
		poly_object<double>::operator+(RhsType&& pRhsObject) {
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
						(machine::instruction_verb::op_add,
							op_return, _M_Operand, pRhsObject._M_Operand);
			
					return RhsType{ *pRhsObject + _M_Value, ""};
		}

			if constexpr
				(std::is_integral_v<typename RhsType::value_type>) {
					machine::operand op_return(*pRhsObject + _M_Value, "");
					cur_module.push_primitive_operator
						(machine::instruction_verb::op_add,
							op_return, _M_Operand, pRhsObject._M_Operand);
			
					return poly_object<double>{ *pRhsObject + _M_Value, ""};
		}
	}

	template <typename RhsType>
	poly_object<double>&
		poly_object<double>::operator+=(RhsType&& pRhsObject) {
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

	template <typename RhsType>
	auto
		poly_object<double>::operator-(RhsType&& pRhsObject) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");

		machine::operand op_return(*pRhsObject + _M_Value, "");
		auto& cur_module = poly_binary::current();
			  cur_module.push_enter();
			  cur_module.push_primitive_operator
					(machine::instruction_verb::op_sub,
						op_return, _M_Operand, pRhsObject._M_Operand);
			
		return poly_object<double>{ *pRhsObject + _M_Value, ""};
	}

	template <typename RhsType>
	poly_object<double>&
		poly_object<double>::operator-=(RhsType&& pRhsObject) {
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

	template <typename RhsType>
	auto
		poly_object<double>::operator*(RhsType&& pRhsObject) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");

		machine::operand op_return(*pRhsObject + _M_Value, "");
		auto& cur_module = poly_binary::current();
			  cur_module.push_enter();
			  cur_module.push_primitive_operator
					(machine::instruction_verb::op_mul,
						op_return, _M_Operand, pRhsObject._M_Operand);
			
		return poly_object<double>{ *pRhsObject + _M_Value, ""};
	}

	template <typename RhsType>
	poly_object<double>&
		poly_object<double>::operator*=(RhsType&& pRhsObject) {
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

	template <typename RhsType>
	auto
		poly_object<double>::operator/(RhsType&& pRhsObject) {
		static_assert
			(std::is_integral_v<typename RhsType::value_type>
				|| std::is_floating_point_v<typename RhsType::value_type>,
					"[AMPERSAND][POLY_OBJECT] Non - Assignable Value Type.");

		machine::operand op_return(*pRhsObject + _M_Value, "");
		auto& cur_module = poly_binary::current();
			  cur_module.push_enter();
			  cur_module.push_primitive_operator
					(machine::instruction_verb::op_div,
						op_return, _M_Operand, pRhsObject._M_Operand);
			
		return poly_object<double>{ *pRhsObject + _M_Value, ""};
	}

	template <typename RhsType>
	poly_object<double>&
		poly_object<double>::operator/=(RhsType&& pRhsObject) {
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

	template <std::floating_point ValueType, typename StringType>
	poly_object(ValueType, StringType) -> poly_object<ValueType>;
}