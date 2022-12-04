#pragma once
#include <type_traits>

namespace ampersand::meta {
	struct and_with		    {};
	struct or_with		    {};

	struct greater_than	    {};
	struct greater_or_equal {};

	struct less_than	    {};
	struct less_or_equal    {};

	struct equal_with	    {};
	struct different_with   {};

	struct not_to		    {}; // Only in Unary Condition.

	template <typename Verb, typename Attribute>
	struct unary_condition {
		unary_condition(Verb, Attribute) {}
		unary_condition()				 {}
	};

	template <typename Verb, typename LAttr, typename RAttr>
	struct binary_condition {
		binary_condition(Verb, LAttr, RAttr) {}
		binary_condition()					 {}

		template <typename RVerb, typename RLField, typename RRField>
		auto
			operator&&
				(binary_condition<RVerb, RLField, RRField> pRhs) { 
			return 
				binary_condition
					<and_with,
						binary_condition<Verb, LAttr, RAttr>,
							binary_condition<RVerb, RLField, RRField>> (and_with{}, *this, pRhs);
		}

		template <typename RVerb, typename RLAttr, typename RRAttr>
		auto
			operator||
				(binary_condition<RVerb, RLAttr, RRAttr> pRhs) {
			return 
				binary_condition
					<or_with,
						binary_condition<Verb, LAttr, RAttr>,
							binary_condition<RVerb, RLAttr, RRAttr>> (or_with {}, *this, pRhs);
		}
	};

	template <typename Verb, typename LAttr, typename RAttr>
	binary_condition(Verb, LAttr, RAttr) ->
		binary_condition
			<std::remove_reference_t<Verb>,
				std::remove_reference_t<LAttr>,
					std::remove_reference_t<RAttr>>;
}