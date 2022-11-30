#pragma once
#include <ampersand/meta/annotation.hpp>

namespace ampersand::meta {
	template <auto ActionT, typename... AnnotationT>
	struct action {
		static constexpr value = ActionT;
		using annotations = boost::mp11::mp_list<Annotation...>;
	};
}