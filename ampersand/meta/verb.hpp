#pragma once
#include <type_traits>

#define AMPERSAND_DECLARE_BINARY(pName, pVerb) using pName = binary_verb<pVerb>;
#define AMPERSAND_DECLARE_UNARY(pName, pVerb)  using pName = unary_verb <pVerb>;
#define AMPERSAND_DECLARE_NARY(pName, pVerb)   using pName = nary_verb  <pVerb>;

namespace ampersand::meta {
	enum class verb {
		no_operation,

		add		,      add_and_store,
		subtract, subtract_and_store,
		multiply, multiply_and_store,
		divide,		divide_and_store,

		and_with, or_with,

		greater_than, greater_or_equal,
		   less_than,    less_or_equal, not_to,

		equal, not_equal,
		move, copy, reference,

		invoke,
		invoke_method,
		invoke_static_method
	};

	template <verb Verb> struct unary_verb  { static inline constexpr verb verb_category = Verb; };
	template <verb Verb> struct binary_verb { static inline constexpr verb verb_category = Verb; };
	template <verb Verb> struct nary_verb   { static inline constexpr verb verb_category = Verb; };

	AMPERSAND_DECLARE_BINARY(and_with, verb::and_with);
	AMPERSAND_DECLARE_BINARY(or_with , verb::or_with) ;

	AMPERSAND_DECLARE_BINARY(greater_than	 , verb::greater_than);
	AMPERSAND_DECLARE_BINARY(greater_or_equal, verb::greater_or_equal);
	
	AMPERSAND_DECLARE_BINARY(less_than	  , verb::less_than);
	AMPERSAND_DECLARE_BINARY(less_or_equal, verb::less_or_equal);


	AMPERSAND_DECLARE_BINARY(equal	  , verb::equal);
	AMPERSAND_DECLARE_BINARY(not_equal, verb::not_equal);

	AMPERSAND_DECLARE_BINARY(add		  , verb::add);
	AMPERSAND_DECLARE_BINARY(add_and_store, verb::add_and_store);

	AMPERSAND_DECLARE_BINARY(subtract		   , verb::subtract);
	AMPERSAND_DECLARE_BINARY(subtract_and_store, verb::subtract_and_store);

	AMPERSAND_DECLARE_BINARY(multiply		   , verb::multiply);
	AMPERSAND_DECLARE_BINARY(multiply_and_store, verb::multiply_and_store);

	AMPERSAND_DECLARE_BINARY(divide			 , verb::divide);
	AMPERSAND_DECLARE_BINARY(divide_and_store, verb::divide_and_store);

	AMPERSAND_DECLARE_BINARY(move	  , verb::move);
	AMPERSAND_DECLARE_BINARY(copy	  , verb::copy);
	AMPERSAND_DECLARE_BINARY(reference, verb::reference);

	AMPERSAND_DECLARE_UNARY (not_to				 , verb::not_to);
	AMPERSAND_DECLARE_NARY  (invoke				 , verb::invoke);
	AMPERSAND_DECLARE_NARY  (invoke_static_method, verb::invoke_static_method);
	AMPERSAND_DECLARE_NARY  (invoke_method		 , verb::invoke_method);
}

namespace ampersand::meta::utility {
	template <typename T>
	struct is_unary_verb				   : std::false_type {};
	template <verb Verb>
	struct is_unary_verb<unary_verb<Verb>> : std::true_type  {};

	template <typename T>
	struct is_binary_verb				     : std::false_type {};
	template <verb Verb>
	struct is_binary_verb<binary_verb<Verb>> : std::true_type  {};

	template <typename T>
	struct is_nary_verb				     : std::false_type {};
	template <verb Verb>
	struct is_nary_verb<nary_verb<Verb>> : std::true_type  {};

	template <typename T>
	struct is_operator_verb
		: std::disjunction
			<
				is_unary_verb <T>,
				is_binary_verb<T>,
				is_nary_verb  <T>
			> {};

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