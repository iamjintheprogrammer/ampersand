#pragma once
#include <ampersand/diopter/loop_header.hpp>

namespace ampersand::diopter {
	template 
		<concepts::loop_header LoopHeader,
		 typename...		   LoopScript>
	class loop {
		using __header_type = LoopHeader;
			  __header_type _M_Header;
		using __tuple_type  = std::tuple<LoopScript...>;
			  __tuple_type  _M_Script;
	public:
		using header_type = LoopHeader;
		loop(header_type pHeader, LoopScript... pScript)
			: _M_Header(pHeader),
			  _M_Script(pScript) {}
		
		header_type& get_loop_header() { return _M_Header; }
	};

	template
		<concepts::loop_header LoopHeader,
		 typename... LoopScript>
	loop(LoopHeader, LoopScript...) -> loop<LoopHeader, LoopScript...>;

namespace utility {
	template <typename AnyType>
	struct is_loop						 : std::false_type { };
	template <typename... LoopElement>
	struct is_loop<loop<LoopElement...>> : std::true_type  { };
	template <typename AnyType>
	inline constexpr bool is_loop_v = is_loop<AnyType>::value;
}

namespace concepts {
	template <typename AnyType>
	concept loop = utility::is_loop_v<AnyType>;
}
}