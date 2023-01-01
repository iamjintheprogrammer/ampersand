#pragma once
#include <type_traits>

namespace ampersand::meta {
	struct unary_verb  {};
	struct binary_verb {};

	struct and_with			: binary_verb {};
	struct or_with			: binary_verb {};

	struct greater_than  	: binary_verb {};
	struct greater_or_equal : binary_verb {};

	struct less_than		: binary_verb {};
	struct less_or_equal	: binary_verb {};

	struct equal		    : binary_verb {};
	struct not_equal		: binary_verb {};

	struct add				  : binary_verb {};
	struct add_and_store	  : binary_verb {};

	struct subtract			  : binary_verb {};
	struct subtract_and_store : binary_verb {};

	struct multiply			  : binary_verb {};
	struct multiply_and_store : binary_verb {};

	struct divide			  : binary_verb {};
	struct divide_and_store	  : binary_verb {};

	struct move				  : binary_verb {};
	struct copy				  : binary_verb {};

	struct not_to		      : unary_verb  {};
}

namespace ampersand::meta::utility {
	template <typename T>
	struct is_operator_verb
		: std::integral_constant
			<bool,std::is_base_of_v<unary_verb, T>
				|| std::is_base_of_v<binary_verb, T>> {};

	template <typename T>
	struct is_binary_verb
		: std::integral_constant
			<bool, std::is_base_of_v<binary_verb, T>> {};

	template <typename T>
	struct is_unary_verb
		: std::integral_constant
			<bool, std::is_base_of_v<unary_verb, T>> {};

	template <typename T>
	inline constexpr bool is_operator_verb_v = is_operator_verb<T>::value;
	template <typename T>
	inline constexpr bool is_binary_verb_v   = is_binary_verb<T>::value;
	template <typename T>
	inline constexpr bool is_unary_verb_v    = is_unary_verb<T>::value;
}

namespace ampersand::meta::concepts {
	template <typename T>
	concept operator_verb = utility::is_operator_verb_v<T>;
	template <typename T>
	concept binary_verb   = utility::is_binary_verb_v<T>;
	template <typename T>
	concept unary_verb    = utility::is_unary_verb_v<T>;
}