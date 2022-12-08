#pragma once
#include <string>
#include <iostream>
#include <ampersand/poly/poly_object.hpp>
#include <ampersand/poly/poly_module.hpp>

namespace ampersand::poly {
	template <>
	class poly_object<> { // Describe "Any" Type.
		using __string_type = std::string;
			  __string_type _M_Name;
	public:
		using value_type  = void;
		using string_type = std::string;

		template <typename... PolyObjects>
		poly_object (string_type, PolyObjects&&...);
		poly_object (); // Temporary Object
		poly_object (poly_object&);
		poly_object (poly_object&&);
		~poly_object();

	public:
		string_type  type_name();
		string_type&	  name();

	public:
		poly_object<>								     operator[](string_type);
		template <typename... ArgObject>  poly_object<>  operator()(string_type, ArgObject&&...);
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
		(string_type pName, PolyObjects&&... pArgument)
			: _M_Name(pName) {
		auto& cur_module	   = poly_module::current();
			  cur_module.push_enter();
		auto  cur_inst
			= instruction(instruction_verb::ob_create, "", 
				operand("", pName), operand(pArgument.type_name(), pArgument.name())...);

		cur_module.push_instruction(cur_inst);
		cur_module.push_leave	   ();
	}

	template <typename... ArgObject>
	poly_object<>
		poly_object<>::operator() (string_type pName, ArgObject&&... pArgs) {
			auto& cur_module = poly_module::current();
				  cur_module.push_enter();
			auto  cur_inst
				= instruction(instruction_verb::call_method, pName,
					operand("", "")		,
					operand("", _M_Name),
					operand(pArgs.type_name(), pArgs.name())...);

			cur_module.push_instruction(cur_inst);
			return poly_object<>{};
	}

	template <typename... ObjectType>
	poly_object<>& 
		poly_object<>::operator= (poly_object<ObjectType...>& pCopy) {
			auto& cur_module = poly_module::current();
			  cur_module.push_enter();
			auto  cur_inst
				= instruction(instruction_verb::move_shallow, "",
					operand("", _M_Name),
					operand(pCopy.type_name(), pCopy.name()));

			cur_module.push_instruction(cur_inst);
			cur_module.push_leave	   ();
			return *this;
	}
	
	template <typename RhsType>
	poly_object<>  
		poly_object<>::operator+(RhsType&& pRhsObject) {
			auto& cur_module = poly_module::current();
				  cur_module.push_enter();

			auto  cur_inst
				= instruction(instruction_verb::op_add, "",
					operand("", ""),
					operand("", _M_Name),
					operand(pRhsObject.type_name(), pRhsObject.name()));

			cur_module.push_instruction(cur_inst);
			return poly_object<>{};
	}

	template <typename RhsType>
	poly_object<>&
		poly_object<>::operator+=(RhsType&& pRhsObject) {
			auto& cur_module = poly_module::current();
				  cur_module.push_enter();

			auto  cur_inst
				= instruction(instruction_verb::op_addeq, "",
					operand("", _M_Name),
					operand(pRhsObject.type_name(), pRhsObject.name()));

			cur_module.push_instruction(cur_inst);
			cur_module.push_leave	   ();

			return *this;
	}

	template <typename RhsType>
	poly_object<>
		poly_object<>::operator-(RhsType&& pRhsObject) {
			auto& cur_module = poly_module::current();
				  cur_module.push_enter();

			auto  cur_inst
				= instruction(instruction_verb::op_sub, "",
					operand("", ""),
					operand("", _M_Name),
					operand(pRhsObject.type_name(), pRhsObject.name()));

			cur_module.push_instruction(cur_inst);
			return poly_object<>{};
	}

	template <typename RhsType>
	poly_object<>&
		poly_object<>::operator-=(RhsType&& pRhsObject) {
			auto& cur_module = poly_module::current();
				  cur_module.push_enter();

			auto  cur_inst
				= instruction(instruction_verb::op_subeq, "",
					operand("", _M_Name),
					operand(pRhsObject.type_name(), pRhsObject.name()));

			cur_module.push_instruction(cur_inst);
			cur_module.push_leave	   ();

			return *this;
	}

	template <typename RhsType>
	poly_object<>
		poly_object<>::operator*(RhsType&& pRhsObject) {
			auto& cur_module = poly_module::current();
				  cur_module.push_enter();

			auto  cur_inst
				= instruction(instruction_verb::op_mul, "",
					operand("", ""),
					operand("", _M_Name),
					operand(pRhsObject.type_name(), pRhsObject.name()));

			cur_module.push_instruction(cur_inst);
			return poly_object<>{};
	}

	template <typename RhsType>
	poly_object<>&
		poly_object<>::operator*=(RhsType&& pRhsObject) {
			auto& cur_module = poly_module::current();
				  cur_module.push_enter();

			auto  cur_inst
				= instruction(instruction_verb::op_muleq, "",
					operand("", _M_Name),
					operand(pRhsObject.type_name(), pRhsObject.name()));

			cur_module.push_instruction(cur_inst);
			cur_module.push_leave	   ();

			return *this;
	}

	template <typename RhsType>
	poly_object<>
		poly_object<>::operator/(RhsType&& pRhsObject) {
			auto& cur_module = poly_module::current();
				  cur_module.push_enter();

			auto  cur_inst
				= instruction(instruction_verb::op_div, "",
					operand("", ""),
					operand("", _M_Name),
					operand(pRhsObject.type_name(), pRhsObject.name()));

			cur_module.push_instruction(cur_inst);
			return poly_object<>{};
	}

	template <typename RhsType>
	poly_object<>&
		poly_object<>::operator/=(RhsType&& pRhsObject) {
			auto& cur_module = poly_module::current();
				  cur_module.push_enter();

			auto  cur_inst
				= instruction(instruction_verb::op_diveq, "",
					operand("", _M_Name),
					operand(pRhsObject.type_name(), pRhsObject.name()));

			cur_module.push_instruction(cur_inst);
			cur_module.push_leave	   ();

			return *this;
	}
}