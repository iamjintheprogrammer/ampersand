#pragma once
#include <type_traits>

#define AMPERSAND_DECLARE_BINARY(pName) struct pName : binary_verb {};
#define AMPERSAND_DECLARE_UNARY(pName)  struct pName : unary_verb  {};
#define AMPERSAND_DECLARE_NARY(pName)   struct pName : nary_verb   {};

namespace ampersand::meta {
	struct unary_verb  {};
	struct binary_verb {};
	struct nary_verb   {};

	AMPERSAND_DECLARE_BINARY(and_with);
	AMPERSAND_DECLARE_BINARY(or_with);

	AMPERSAND_DECLARE_BINARY(greater_than);
	AMPERSAND_DECLARE_BINARY(greater_or_equal);
	
	AMPERSAND_DECLARE_BINARY(less_than);
	AMPERSAND_DECLARE_BINARY(less_or_equal);


	AMPERSAND_DECLARE_BINARY(equal);
	AMPERSAND_DECLARE_BINARY(not_equal);

	AMPERSAND_DECLARE_BINARY(add);
	AMPERSAND_DECLARE_BINARY(add_and_store);

	AMPERSAND_DECLARE_BINARY(subtract);
	AMPERSAND_DECLARE_BINARY(subtract_and_store);

	AMPERSAND_DECLARE_BINARY(multiply);
	AMPERSAND_DECLARE_BINARY(multiply_and_store);

	AMPERSAND_DECLARE_BINARY(divide);
	AMPERSAND_DECLARE_BINARY(divide_and_store);

	AMPERSAND_DECLARE_BINARY(move);
	AMPERSAND_DECLARE_BINARY(copy);
	AMPERSAND_DECLARE_BINARY(reference);

	AMPERSAND_DECLARE_UNARY (not_to);
	AMPERSAND_DECLARE_NARY  (invoke);
	AMPERSAND_DECLARE_NARY  (invoke_static_method);
	AMPERSAND_DECLARE_NARY  (invoke_method);
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