#pragma once
#include <ampersand/diopter/script.hpp>
#include <ampersand/diopter/describer_trait.hpp>

namespace ampersand::diopter {
	template <concepts::script Script, typename Traits = describer_trait<Script>>
	class basic_describer {
	public:
		using traits_type	  = Traits;
		using value_type      = typename traits_type::value_type;
		
		using reference		  = typename traits_type::reference		 ;
		using const_reference = typename traits_type::const_reference;

		using pointer		  = typename traits_type::pointer	   ;
		using const_pointer   = typename traits_type::const_pointer;

		using iterator        = typename traits_type::iterator		  ;
		using const_iterator  = typename traits_type::const_iterator  ;

	public:
		basic_describer(concepts::script auto&& pScript) : _M_Script(pScript) {}
		body_type operator()();
	};
}