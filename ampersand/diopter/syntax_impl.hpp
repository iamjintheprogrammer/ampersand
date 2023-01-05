#pragma once
#include <vector>
#include <memory>

#include <ampersand/diopter/operand.hpp>

namespace ampersand::diopter  {

	class syntax_impl {
		friend class syntax;
		using		name_type_impl = operand_dynamic_impl::name_type;
		struct syntax_operand_impl {
			enum class category_impl { syntax, operand, none };
			category_impl				 _M_Impl_Category;
			std::shared_ptr<syntax_impl> _M_Impl_Syntax  ;
			operand						 _M_Impl_Operand ;


			 syntax_operand_impl();
			 syntax_operand_impl(const syntax_operand_impl&);
			 syntax_operand_impl(meta::concepts::meta_operator auto&);
			 syntax_operand_impl(name_type_impl			 , name_type_impl);
			 syntax_operand_impl(meta::primitive_category, name_type_impl);
			 syntax_operand_impl(std::integral	     auto);
			 syntax_operand_impl(std::floating_point auto);
			~syntax_operand_impl();
		};

		std::vector<syntax_operand_impl> _M_Impl_Operand;
		meta::verb						 _M_Impl_Verb   ;

		template <typename... T>
		void _M_Impl_Init(meta::basic_meta_object<T...>&);
		void _M_Impl_Init(std::integral		  auto);
		void _M_Impl_Init(std::floating_point auto);
		void _M_Impl_Init(meta::concepts::meta_operator auto&);
		template <std::size_t... Idx, typename V, typename... T>
		void _M_Impl_Init(meta::meta_operator<V, T...>&, std::index_sequence<Idx...>);
		template <std::size_t Idx, typename V, typename... T>
		void _M_Impl_Init(meta::meta_operator<V, T...>&);

	public:
		using name_type		  = name_type_impl;
		using size_type		  = std::size_t;
		using difference_type = std::ptrdiff_t;
		using category		  = syntax_operand_impl::category_impl;

		template <typename V, typename... T>
		syntax_impl(meta::meta_operator<V, T...>&);

		syntax_operand_impl* operator[]	 (size_type);
		size_type			 operand_count();
		meta::verb			 get_verb	  ();
	};

	syntax_impl::syntax_operand_impl::syntax_operand_impl
		(meta::concepts::meta_operator auto& pOperator)
			: _M_Impl_Syntax  (std::make_shared<syntax_impl>(pOperator)),
			  _M_Impl_Category(category::syntax) {}

	template <typename... T>
	void
		syntax_impl::_M_Impl_Init
			(meta::basic_meta_object<T...>& pMetaType) {
		_M_Impl_Operand.emplace_back
			(pMetaType.type_of().type_id(), pMetaType.name());
	}

	void
		syntax_impl::_M_Impl_Init
			(std::integral auto pValue) {
		_M_Impl_Operand.emplace_back(pValue);
	}

	void
		syntax_impl::_M_Impl_Init
			(std::floating_point auto pValue) {
		_M_Impl_Operand.emplace_back(pValue);
	}

	void
		syntax_impl::_M_Impl_Init
			(meta::concepts::meta_operator auto& pOperator) {
		_M_Impl_Operand.emplace_back(pOperator);
	}

	template <std::size_t... Idx, typename V, typename... T>
	void
		syntax_impl::_M_Impl_Init
			(meta::meta_operator<V, T...>& pMeta, std::index_sequence<Idx...>) {
		((_M_Impl_Init<Idx>(pMeta)), ...);
	}

	template <std::size_t Idx, typename V, typename... T>
	void
		syntax_impl::_M_Impl_Init
			(meta::meta_operator<V, T...>& pMeta) {
		_M_Impl_Init(meta::get_operand<Idx>(pMeta));
	}

	syntax_impl::syntax_operand_impl::syntax_operand_impl
		(std::integral auto pValue)
			: _M_Impl_Operand (pValue),
			  _M_Impl_Category(category::operand) {}

	syntax_impl::syntax_operand_impl::syntax_operand_impl
		(std::floating_point auto pValue)
			: _M_Impl_Operand (pValue),
			  _M_Impl_Category(category::operand) {}

	template <typename V, typename... T>
	syntax_impl::syntax_impl
		(meta::meta_operator<V, T...>& pMeta)
			: _M_Impl_Verb(meta::meta_operator<V, T...>::verb::verb_category){
			_M_Impl_Init(pMeta, std::make_index_sequence<sizeof...(T)>{});
	}

}