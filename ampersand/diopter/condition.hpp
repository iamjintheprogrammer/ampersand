#pragma once
#include <ampersand/meta.hpp>

namespace ampersand::diopter {
	template
		<meta::concepts::conditional_operator Condition,
		 typename...						  Scripts>
	class condition {
		using __condition_type = Condition;
			  __condition_type _M_Condition;
		using __tuple_type	   = std::tuple<Scripts...>;
			  __tuple_type	   _M_Script;
	public:
		using condition_type = __condition_type;
		constexpr condition
			(condition_type pCondition, Scripts... pScript)
				: _M_Condition(pCondition),
				  _M_Script	  (pScript)   {  }

		condition_type& get_condition() { return _M_Condition; }
	};

	template <meta::concepts::conditional_operator Condition, typename... Scripts>
	condition(Condition, Scripts...) -> condition<Condition, Scripts...>;

namespace utility {
	template <typename AnyType>
	struct is_condition									: std::false_type {};
	template <typename... ConditionElement>
	struct is_condition<condition<ConditionElement...>> : std::true_type  {};
	template <typename AnyType>
	inline constexpr bool is_condition_v = is_condition<AnyType>::value;
}

namespace concepts {
	template <typename AnyType>
	concept condition = utility::is_condition_v<AnyType>;
}
}