#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <ampersand/schema/condition.hpp>

namespace ampersand::schema {
	template <typename... AnyType>
	class field;

	template <typename FieldT, typename... FieidAnnotation>
	class field <meta::attribute<FieldT, FieidAnnotation...>>
		: public meta::attribute<FieldT, FieidAnnotation...> {
	public:
		using field_type	  = FieldT;
		using field_meta_type = meta::attribute<FieldT, FieidAnnotation...>;

		constexpr field(meta::attribute<FieldT, FieidAnnotation...>) : field_meta_type() {} // For CTAD Support
		constexpr field()											 : field_meta_type() {} // For Aliased Initialization

	public:
		template <typename Rhs>
		auto operator<  (Rhs&& pRhs) { 
			return 
				syntax::binary_condition
					(syntax::less_than{}, *this, pRhs); 
		}

		template <typename Rhs>
		auto operator<= (Rhs&& pRhs) { 
			return 
				syntax::binary_condition
					(syntax::less_or_equal{}, *this, pRhs); 
		}

		template <typename Rhs>
		auto operator>  (Rhs&& pRhs) { 
			return 
				syntax::binary_condition
					(syntax::larger_than{}, *this, pRhs); 
		}

		template <typename Rhs>
		auto operator>= (Rhs&& pRhs) { 
			return 
				syntax::binary_condition
					(syntax::larger_or_equal{}, *this, pRhs); 
		}

		template <typename Rhs>
		auto operator== (Rhs&& pRhs) { 
			return 
				syntax::binary_condition
					(syntax::equal_with{}, *this, pRhs); 
		}

		template <typename Rhs>
		auto operator!= (Rhs&& pRhs) { 
			return 
				syntax::binary_condition
					(syntax::different_with{}, *this, pRhs); 
		}
	};

	template <typename FieldT, typename... FieldAnnotation>
	field
		(meta::attribute<FieldT, FieldAnnotation...>)
			-> field
					<meta::attribute<FieldT, FieldAnnotation...>>;
}