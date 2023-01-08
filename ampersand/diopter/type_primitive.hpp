#pragma once
#include <ampersand/meta.hpp>
#include <ampersand/diopter/type.hpp>

namespace ampersand::diopter {
	class primitive : public type {
		meta::primitive_category impl_category;

		primitive(meta::concepts::primitive auto);
	public:
		meta::primitive_category primitive_category();
	};
}