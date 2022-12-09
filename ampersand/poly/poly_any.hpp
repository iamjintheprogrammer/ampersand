#pragma once
#include <string>
#include <iostream>
#include <ampersand/poly/poly_object.hpp>
#include <ampersand/poly/poly_binary.hpp>

namespace ampersand::poly {
	template <>
	class poly_object<> { // Describe "Any" Type.
		template <typename... AnyType> friend class poly_object;
		using __operand_type = machine::operand;
			  __operand_type _M_Operand;
	public:
		template <typename... PolyObjects>
		poly_object (const char*, PolyObjects&&...);
		poly_object (); // Temporary Object
		poly_object (poly_object&);
		poly_object (poly_object&&);
		~poly_object();

	public:
		poly_object<>								     operator[](const char*);
		template <typename... ArgObject>  poly_object<>  operator()(const char*, ArgObject&&...);
		template <typename... ObjectType> poly_object<>& operator= (poly_object<ObjectType...>&);
										  poly_object<>& operator= (poly_object<>&);
										  poly_object<>& operator= (poly_object<>&&);

		template <typename RhsType>		  poly_object<>  operator+ (RhsType&&);
		template <typename RhsType>		  poly_object<>& operator+=(RhsType&&);
		template <typename RhsType>		  poly_object<>  operator- (RhsType&&);
		template <typename RhsType>		  poly_object<>& operator-=(RhsType&&);
		template <typename RhsType>		  poly_object<>  operator* (RhsType&&);
		template <typename RhsType>		  poly_object<>& operator*=(RhsType&&);
		template <typename RhsType>		  poly_object<>  operator/ (RhsType&&);
		template <typename RhsType>		  poly_object<>& operator/=(RhsType&&);

	};

	using any = poly_object<>;

	template <typename... PolyObjects>
	poly_object<>::poly_object
		(const char* pName, PolyObjects&&... pArgument) : _M_Operand("", pName) {
		auto& cur_module = poly_binary::current();
			  cur_module.push_enter		   ();
			  cur_module.push_object_create(_M_Operand, pArgument._M_Operand...);
			  cur_module.push_leave	       ();
	}

	template <typename... ArgObject>
	poly_object<>
		poly_object<>::operator() (const char* pName, ArgObject&&... pArgs) {
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_call_method
					(pName, _M_Operand, machine::operand("", ""), pArgs._M_Operand...);

			return poly_object<>{};
	}

	template <typename... ObjectType>
	poly_object<>& 
		poly_object<>::operator= (poly_object<ObjectType...>& pCopy) {
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter		  ();
				  cur_module.push_shallow_move(_M_Operand, pCopy._M_Operand);
				  cur_module.push_leave	      ();
			return *this;
	}
	
	template <typename RhsType>
	poly_object<>  
		poly_object<>::operator+(RhsType&& pRhsObject) {
			machine::operand op_return("", "");
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_primitive_operator
						(machine::instruction_verb::op_add, 
							op_return, _M_Operand, pRhsObject._M_Operand);

			return poly_object<>{};
	}

	template <typename RhsType>
	poly_object<>&
		poly_object<>::operator+=(RhsType&& pRhsObject) {
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_primitive_operator
						(machine::instruction_verb::op_addeq,
							_M_Operand, _M_Operand, pRhsObject._M_Operand);
				  cur_module.push_leave();

			return *this;
	}

	template <typename RhsType>
	poly_object<>
		poly_object<>::operator-(RhsType&& pRhsObject) {
			machine::operand op_return("", "");
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_primitive_operator
						(machine::instruction_verb::op_sub,
							op_return, _M_Operand, pRhsObject._M_Operand);

			return poly_object<>{};
	}

	template <typename RhsType>
	poly_object<>&
		poly_object<>::operator-=(RhsType&& pRhsObject) {
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_primitive_operator
						(machine::instruction_verb::op_subeq,
							_M_Operand, _M_Operand, pRhsObject._M_Operand);
				  cur_module.push_leave();

			return *this;
	}

	template <typename RhsType>
	poly_object<>
		poly_object<>::operator*(RhsType&& pRhsObject) {
			machine::operand op_return("", "");
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_primitive_operator
						(machine::instruction_verb::op_mul,
							op_return, _M_Operand, pRhsObject._M_Operand);

			return poly_object<>{};
	}

	template <typename RhsType>
	poly_object<>&
		poly_object<>::operator*=(RhsType&& pRhsObject) {
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_primitive_operator
						(machine::instruction_verb::op_muleq,
							_M_Operand, _M_Operand, pRhsObject._M_Operand);
				  cur_module.push_leave();

			return *this;
	}

	template <typename RhsType>
	poly_object<>
		poly_object<>::operator/(RhsType&& pRhsObject) {
			machine::operand op_return("", "");
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_primitive_operator
						(machine::instruction_verb::op_div,
							op_return, _M_Operand, pRhsObject._M_Operand);

			return poly_object<>{};
	}

	template <typename RhsType>
	poly_object<>&
		poly_object<>::operator/=(RhsType&& pRhsObject) {
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_primitive_operator
						(machine::instruction_verb::op_diveq,
							_M_Operand, _M_Operand, pRhsObject._M_Operand);
				  cur_module.push_leave();

			return *this;
	}
}