#pragma once
#include <ampersand/meta.hpp>
#include <ampersand/diopter/type.hpp>

namespace ampersand::diopter {
	class primitive : public type {
		meta::primitive_category impl_category;

		 primitive(meta::concepts::primitive auto);
	public:
		~primitive();
		meta::primitive_category primitive_category();
	};

	primitive::primitive
		(meta::concepts::primitive auto pPrimitive)
			: impl_category(pPrimitive.type_id()),
			  type		   (type::category::primitive) {}
}