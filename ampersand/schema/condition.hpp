#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

namespace ampersand::schema::syntax {
	struct and_with		   {};
	struct or_with		   {};

	struct larger_than	   {};
	struct larger_or_equal {};

	struct less_than	   {};
	struct less_or_equal   {};

	struct equal_with	   {};
	struct different_with  {};

	template <typename Verb, typename LField, typename RField>
	struct binary_condition {
		binary_condition(Verb, LField, RField) {}
		binary_condition()					   {}

		template <typename RVerb, typename RLField, typename RRField>
		auto
			operator&&
				(binary_condition<RVerb, RLField, RRField> pRhs) { 
			return 
				binary_condition
					<and_with,
						binary_condition<Verb, LField, RField>,
							binary_condition<RVerb, RLField, RRField>> (and_with{}, *this, pRhs);
		}

		template <typename RVerb, typename RLField, typename RRField>
		auto
			operator||
				(binary_condition<RVerb, RLField, RRField> pRhs) { 
			return 
				binary_condition
					<or_with,
						binary_condition<Verb, LField, RField>,
							binary_condition<RVerb, RLField, RRField>> (or_with {}, *this, pRhs);
		}
	};

	template <typename Verb, typename LField, typename RField>
	binary_condition(Verb, LField, RField) ->
		binary_condition
			<std::remove_reference_t<Verb>  ,
			 std::remove_reference_t<LField>,
			 std::remove_reference_t<RField>>;
}