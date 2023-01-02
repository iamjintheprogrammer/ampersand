#pragma once
#include <ampersand/diopter/declare.hpp>

namespace ampersand::diopter::utility {
	template <typename AnyType>
	struct is_component_element
		: std::bool_constant
			<
				meta::utility::is_meta_object_v <AnyType> ||
					  utility::is_declare_v	    <AnyType> ||
					  utility::is_type_declare_v<AnyType>
			> {};

	template <typename AnyType>
	inline constexpr bool is_component_element_v = is_script_component<AnyType>::value;
}

namespace ampersand::diopter::concepts {
	template <typename AnyType>
	concept component_element = utility::is_component_element_v<AnyType>;
}