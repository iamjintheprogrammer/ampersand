#pragma once
#include <vector>
#include <memory>

#include <ampersand/diopter/syntax/syntax_element.hpp>
#include <ampersand/diopter/syntax/syntax_element_constant.hpp>
#include <ampersand/diopter/syntax/syntax_element_object.hpp>

namespace ampersand::diopter::syntax {
	class syntax : public element {
		meta::verb							  impl_verb   ;
		std::vector<std::shared_ptr<element>> impl_element;
		element								  impl_element_error { element::element_category::none };

		template					 <typename V, typename... T> void impl_init(meta::meta_operator<V, T...>&);
		template <std::size_t... Idx, typename V, typename... T> void impl_init(meta::meta_operator<V, T...>&, std::index_sequence<Idx...>);

		void impl_do_init(meta::concepts::meta_operator auto);
		void impl_do_init(meta::concepts::meta_object   auto);
		void impl_do_init(std::integral				    auto);
		void impl_do_init(std::floating_point		    auto);
	public:
		using size_type = decltype(impl_element)::size_type;
		using name_type = std::string;

		syntax(meta::concepts::meta_operator auto);
		element& operator[](size_type);
	};

	syntax::syntax
		(meta::concepts::meta_operator auto pOperator)
			: impl_verb(decltype(pOperator)::verb::verb_category) {
		impl_init(pOperator);
	}

	template <typename V, typename... T>
	void
		syntax::impl_init
			(meta::meta_operator<V, T...>& pOperator) {
		impl_init(pOperator, std::make_index_sequence<sizeof...(T)>{});
	}
	
	template <std::size_t... Idx, typename V, typename... T>
	void
		syntax::impl_init
			(meta::meta_operator<V, T...>& pOperator, std::index_sequence<Idx...>) {
		((impl_do_init(meta::get_operand<Idx>(pOperator))), ...);
	}

	void 
		syntax::impl_do_init
			(meta::concepts::meta_operator auto pOperator) {
		impl_verb.push_back
			(std::shared_ptr<element>(new syntax(pOperator)));
	}

	void
		syntax::impl_do_init
			(meta::concepts::meta_object auto pObject) {
		impl_verb.push_back
			(std::shared_ptr<element>(new object(pObject.name(), pObject.type_of().type_id())))
	}

	void
		syntax::impl_do_init
			(std::integral auto pValue) {
		impl_verb.push_back
			(std::shared_ptr<element>(new constant(pValue)));
	}

	void
		syntax::impl_do_init
			(std::floating_point auto pValue) {
		impl_verb.push_back
			(std::shared_ptr<element>(new constant(pValue)));
	}
}