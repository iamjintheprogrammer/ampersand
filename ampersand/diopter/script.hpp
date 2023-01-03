#pragma once
#include <ampersand/diopter/condition.hpp>
#include <ampersand/diopter/loop.hpp>

namespace ampersand::diopter {
namespace utility		     {
	template <typename AnyType>
	struct is_script_element
		: std::disjunction
			<
				utility::is_loop_v	   <AnyType>,
				utility::is_condition_v<AnyType>,

				meta::utility::is_meta_object_v<AnyType>,
				meta::utility::is_meta_type_v  <AnyType>
			>{};

	template <typename AnyType>
	inline constexpr bool is_script_element_v = is_script_element<AnyType>::value;
}

namespace concepts {
	template <typename AnyType>
	concept script_element = utility::is_script_element_v<AnyType>;
}

	template <concepts::script_element... Elements>
	class script {
		using __tuple_type = std::tuple<Elements...>;
			  __tuple_type _M_Element;
	public:
		script(Elements... pElement)
			: _M_Element(pElement) {  }
	};

	template <concepts::script_element... Elements>
	script(Elements...) -> script<Elements...>;

namespace utility {
	template <typename AnyType>
	struct is_script					  : std::false_type {};
	template <concepts::script_element... Elements>
	struct is_script<script<Elements...>> : std::true_type  {};
	template <typename AnyType>
	inline constexpr bool is_script_v = is_script<AnyType>::value;
}

namespace concepts {
	template <typename AnyType>
	concept script = utility::is_script_v<AnyType>;
}
}