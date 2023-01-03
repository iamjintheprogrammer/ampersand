#pragma once
#include <ampersand/diopter/script.hpp>

namespace ampersand::diopter {
	template <concepts::script Script>
	class describer_trait {
	public:
		using body_type   = std::string;
		using script_type = Script;
	public:
		static bool describe(body_type&, script_type&);
		
	};
}