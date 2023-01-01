#pragma once
#include <tuple>
#include <type_traits>

#include <ampersand/meta/operator_verb.hpp>
#include <ampersand/meta/details/operator.hpp>

namespace ampersand::meta {
	template <typename Verb, typename... Operand>
	class meta_operator {
		static_assert(sizeof...(Operand) > 0, "[AMPERSAND][META] No Operand Provided.");
		using __tuple = std::tuple<Operand...>;
			  __tuple _M_Base;
	
	public:
		using verb = Verb;

		meta_operator(verb, Operand&... pOperand) : _M_Base(pOperand...) {}
		meta_operator	   (Operand&... pOperand) : _M_Base(pOperand...) {}

		template <std::size_t Idx>	   constexpr auto get_operand();

		template <typename... RhsType> auto operator+  (meta_operator<RhsType...>&);
		template <typename... RhsType> auto operator+= (meta_operator<RhsType...>&);

		template <typename... RhsType> auto operator-  (meta_operator<RhsType...>&);
		template <typename... RhsType> auto operator-= (meta_operator<RhsType...>&);

		template <typename... RhsType> auto operator*  (meta_operator<RhsType...>&);
		template <typename... RhsType> auto operator*= (meta_operator<RhsType...>&);

		template <typename... RhsType> auto operator/  (meta_operator<RhsType...>&);
		template <typename... RhsType> auto operator/= (meta_operator<RhsType...>&);

		template <typename... RhsType> auto operator<  (meta_operator<RhsType...>&);
		template <typename... RhsType> auto operator<= (meta_operator<RhsType...>&);

		template <typename... RhsType> auto operator>  (meta_operator<RhsType...>&);
		template <typename... RhsType> auto operator>= (meta_operator<RhsType...>&);

		template <typename... RhsType> auto operator== (meta_operator<RhsType...>&);
		template <typename... RhsType> auto operator!= (meta_operator<RhsType...>&);

		template <typename... RhsType> auto operator&& (meta_operator<RhsType...>&);
		template <typename... RhsType> auto operator|| (meta_operator<RhsType...>&);

		template <typename... RhsType> auto operator= (meta_operator<RhsType...>&) ;
		template <typename... RhsType> auto operator= (meta_operator<RhsType...>&&);

									   auto operator!  ();
	};

	template <typename Verb, typename... Operand>
	meta_operator(Verb, Operand&...) -> meta_operator<Verb, Operand...>;

	template <typename Verb, typename... Operand>
	template <std::size_t Idx>
	constexpr auto
		meta_operator<Verb, Operand...>::get_operand() {
			return
				std::get<Idx>(_M_Base);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto 
		meta_operator<Verb, Operand...>::operator+
			(meta_operator<RhsType...>& pRhs) {
		return
			meta_operator
				<add,
				 meta_operator<Verb, Operand...>,
				 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto
		meta_operator<Verb, Operand...>::operator+=
			(meta_operator<RhsType...>& pRhs) {
		return
			meta_operator
				<add_and_store,
				 meta_operator<Verb, Operand...>,
				 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto
		meta_operator<Verb, Operand...>::operator-
			(meta_operator<RhsType...>& pRhs) {
		return
			meta_operator
				<subtract,
				 meta_operator<Verb, Operand...>,
				 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto
		meta_operator<Verb, Operand...>::operator-=
			(meta_operator<RhsType...>& pRhs) {
		return
			meta_operator
				<subtract_and_store,
				 meta_operator<Verb, Operand...>,
				 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto
		meta_operator<Verb, Operand...>::operator*
			(meta_operator<RhsType...>& pRhs) {
		return
			meta_operator
				<multiply,
				 meta_operator<Verb, Operand...>,
				 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto
		meta_operator<Verb, Operand...>::operator*=
			(meta_operator<RhsType...>& pRhs) {
		return
			meta_operator
				<multiply_and_store,
				 meta_operator<Verb, Operand...>,
				 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto
		meta_operator<Verb, Operand...>::operator/
			(meta_operator<RhsType...>& pRhs) {
		return
			meta_operator
				<divide,
				 meta_operator<Verb, Operand...>,
				 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto
		meta_operator<Verb, Operand...>::operator/=
			(meta_operator<RhsType...>& pRhs) {
		return
			meta_operator
				<divide_and_store,
				 meta_operator<Verb, Operand...>,
				 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto 
		meta_operator<Verb, Operand...>::operator<
			(meta_operator<RhsType...>& pRhs) {
		return
			meta_operator
				<less_than,
				 meta_operator<Verb, Operand...>,
				 meta_operator<RhsType...>>  (*this, pRhs);
	}


	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto meta_operator<Verb, Operand...>::operator<=
		(meta_operator<RhsType...>& pRhs) {
			return
				meta_operator
					<less_or_equal,
					 meta_operator<Verb, Operand...>,
					 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto meta_operator<Verb, Operand...>::operator>
		(meta_operator<RhsType...>& pRhs) {
			return
				meta_operator
					<greater_than,
					 meta_operator<Verb, Operand...>,
					 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto meta_operator<Verb, Operand...>::operator>=
		(meta_operator<RhsType...>& pRhs) {
			return
				meta_operator
					<greater_or_equal,
					 meta_operator<Verb, Operand...>,
					 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto meta_operator<Verb, Operand...>::operator==
		(meta_operator<RhsType...>& pRhs) {
			return
				meta_operator
					<equal,
					 meta_operator<Verb, Operand...>,
					 meta_operator<RhsType...>>  (*this, pRhs);
	}
	
	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto meta_operator<Verb, Operand...>::operator!=
		(meta_operator<RhsType...>& pRhs) {
			return
				meta_operator
					<not_equal,
					 meta_operator<Verb, Operand...>,
					 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto meta_operator<Verb, Operand...>::operator&&
		(meta_operator<RhsType...>& pRhs) {
			return
				meta_operator
					<and_with,
					 meta_operator<Verb, Operand...>,
					 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto meta_operator<Verb, Operand...>::operator||
		(meta_operator<RhsType...>& pRhs) {
			return
				meta_operator
					<or_with,
					 meta_operator<Verb, Operand...>,
					 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto meta_operator<Verb, Operand...>::operator=
		(meta_operator<RhsType...>& pRhs) {
			return
				meta_operator
					<copy,
					 meta_operator<Verb, Operand...>,
					 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	template <typename... RhsType>
	auto meta_operator<Verb, Operand...>::operator=
		(meta_operator<RhsType...>&& pRhs) {
			return
				meta_operator
					<move,
					 meta_operator<Verb, Operand...>,
					 meta_operator<RhsType...>>  (*this, pRhs);
	}

	template <typename Verb, typename... Operand>
	auto meta_operator<Verb, Operand...>::operator!  () {
		return
			meta_operator
			<not_to,
			 meta_operator<Verb, Operand...>>  (*this);
	}
}

namespace ampersand::meta::utility {
	template <typename... AnyType>
	struct is_meta_operator							   : std::false_type {};
	template <typename... Operand>
	struct is_meta_operator<meta_operator<Operand...>> : std::true_type  {};
	template <typename... AnyType>
	inline constexpr bool is_meta_operator_v = is_meta_operator<AnyType...>::value;

	template <typename... AnyType>
	struct is_and_with						 : std::false_type {};
	template <typename... Operand>
	struct is_and_with<and_with, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_and_with_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_or_with					   : std::false_type {};
	template <typename... Operand>
	struct is_or_with<or_with, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_or_with_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_greater_than							 : std::false_type {};
	template <typename... Operand>
	struct is_greater_than<greater_than, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_greater_than_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_greater_or_equal								 : std::false_type {};
	template <typename... Operand>
	struct is_greater_or_equal<greater_or_equal, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_greater_or_equal_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_less_than						   : std::false_type {};
	template <typename... Operand>
	struct is_less_than<less_than, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_less_than_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_less_or_equal							   : std::false_type {};
	template <typename... Operand>
	struct is_less_or_equal<less_or_equal, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_less_or_equal_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_equal					   : std::false_type {};
	template <typename... Operand>
	struct is_equal<equal, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_equal_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_not_equal						   : std::false_type {};
	template <typename... Operand>
	struct is_not_equal<not_equal, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_not_equal_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_add				   : std::false_type {};
	template <typename... Operand>
	struct is_add<add, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_add_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_add_and_store							   : std::false_type {};
	template <typename... Operand>
	struct is_add_and_store<add_and_store, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_add_and_store_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_subtract				   : std::false_type {};
	template <typename... Operand>
	struct is_subtract<add, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_subtract_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_subtract_and_store						    : std::false_type {};
	template <typename... Operand>
	struct is_subtract_and_store<add_and_store, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_subtract_and_store_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_multiply				   : std::false_type {};
	template <typename... Operand>
	struct is_multiply<add, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_multiply_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_multiply_and_store							   : std::false_type {};
	template <typename... Operand>
	struct is_multiply_and_store<add_and_store, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_multiply_and_store_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_divide				   : std::false_type {};
	template <typename... Operand>
	struct is_divide<add, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_divide_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_divide_and_store							   : std::false_type {};
	template <typename... Operand>
	struct is_divide_and_store<add_and_store, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_divide_and_store_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_move					 : std::false_type {};
	template <typename... Operand>
	struct is_move<move, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_move_v = is_move<AnyType...>::value;

	template <typename... AnyType>
	struct is_copy					 : std::false_type {};
	template <typename... Operand>
	struct is_copy<copy, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_copy_v = is_copy<AnyType...>::value;

	template <typename... AnyType>
	struct is_not_to							: std::false_type {};
	template <typename... Operand>
	struct is_not_to<add_and_store, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_not_to_v = is_not_to<AnyType...>::value;
}

namespace ampersand::meta::concepts {
	template <typename... AnyType>
	concept meta_operator = utility::is_meta_operator_v<AnyType...>;
	
	template <typename... AnyType>
	concept and_with = utility::is_and_with_v<AnyType...>;
	template <typename... AnyType>
	concept or_with  = utility::is_or_with_v<AnyType...>;
	
	template <typename... AnyType>
	concept greater_than = utility::is_greater_than_v<AnyType...>;
	template <typename... AnyType>
	concept greater_or_equal = utility::is_greater_or_equal_v<AnyType...>;

	template <typename... AnyType>
	concept less_than = utility::is_less_than_v<AnyType...>;
	template <typename... AnyType>
	concept less_or_equal = utility::is_less_or_equal_v<AnyType...>;

	template <typename... AnyType>
	concept equal	  = utility::is_equal_v<AnyType...>;
	template <typename... AnyType>
	concept not_equal = utility::is_not_equal_v<AnyType...>;

	template <typename... AnyType>
	concept add			  = utility::is_add_v<AnyType...>;
	template <typename... AnyType>
	concept add_and_store = utility::is_add_and_store_v<AnyType...>;

	template <typename... AnyType>
	concept subtract = utility::is_subtract_v<AnyType...>;
	template <typename... AnyType>
	concept subtract_and_store = utility::is_subtract_and_store_v<AnyType...>;

	template <typename... AnyType>
	concept multiply = utility::is_multiply_v<AnyType...>;
	template <typename... AnyType>
	concept multiply_and_store = utility::is_multiply_and_store_v<AnyType...>;

	template <typename... AnyType>
	concept divide = utility::is_divide_v<AnyType...>;
	template <typename... AnyType>
	concept divide_and_store = utility::is_divide_and_store_v<AnyType...>;

	template <typename... AnyType>
	concept move = utility::is_move_v<AnyType...>;
	template <typename... AnyType>
	concept copy = utility::is_copy_v<AnyType...>;

	template <typename... AnyType>
	concept not_to = utility::is_not_to_v<AnyType...>;
}