#pragma once
#include <ampersand/meta.hpp>
#include <ampersand/diopter/syntax_impl.hpp>

namespace ampersand::diopter {
	class syntax {
		friend class function;

		syntax_impl* _M_Impl	 ;
		bool		 _M_Impl_Root;
		syntax(syntax_impl&);
		syntax();
	public:
		class syntax_operand {
			friend class syntax;
			syntax_impl::syntax_operand_impl* _M_Impl;
			syntax_operand(syntax_impl::syntax_operand_impl*);
		public:
			using category = syntax_impl::category;
			
			category get_category ();
			syntax	 get_syntax   ();
			operand	 get_operand  ();
					 operator bool();
		};

	public:
		using	    name_type = syntax_impl::name_type;
		using	    size_type = syntax_impl::size_type;
		using difference_type = syntax_impl::difference_type;		

		template <typename V, typename... T>
		syntax(meta::meta_operator<V, T...>&);
		
		syntax_operand operator[]   (size_type);
					   operator bool();
		size_type      opreand_count();
		meta::verb     get_verb		();
	};

	template <typename V, typename... T>
	syntax::syntax(meta::meta_operator<V, T...>& pMetaOperator)
		: _M_Impl_Root(true),
		  _M_Impl	  (new syntax_impl(pMetaOperator)) {}
}