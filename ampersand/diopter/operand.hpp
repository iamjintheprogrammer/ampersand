#pragma once
#include <ampersand/diopter/operand_impl.hpp>

namespace ampersand::diopter {
	class operand {
		operand_impl _M_Impl;
	public:
		using   name_type = operand_impl::name_type;

		operand();
		operand(const operand&);
		operand(name_type				, name_type);
		operand(meta::primitive_category, name_type);
		operand(std::integral		auto);
		operand(std::floating_point auto);

	public:
		bool get_value(std::integral	   auto&);
		bool get_value(std::floating_point auto&);

		name_type type_name();
		name_type	   name();

		operand& operator=	  (const operand&);
				 operator bool();
	};

	operand::operand(std::integral		 auto pValue) : _M_Impl(pValue) {}
	operand::operand(std::floating_point auto pValue) : _M_Impl(pValue) {}

	bool operand::get_value(std::integral	    auto& pValue) { _M_Impl.get_value(pValue); }
	bool operand::get_value(std::floating_point auto& pValue) { _M_Impl.get_value(pValue); }
}