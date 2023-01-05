#pragma once
#include <vector>
#include <memory>

#include <ampersand/diopter/operation.hpp>

namespace ampersand::diopter  {

	class syntax_impl {
		using		name_type_impl = operand_dynamic_impl::name_type;
		struct syntax_operand_impl {
			struct		   none_impl {};
			enum class category_impl { syntax, operand, none };

			union syntax_operand_union_impl {
				std::unique_ptr<syntax_impl> u_syntax ;
				operand						 u_operand;
				none_impl					 u_none   ;

				 syntax_operand_union_impl(meta::concepts::meta_operator auto&);
				 syntax_operand_union_impl(name_type_impl		   , name_type_impl);
				 syntax_operand_union_impl(meta::primitive_category, name_type_impl);
				 syntax_operand_union_impl(std::integral	   auto pValue) : u_operand(pValue) {}
				 syntax_operand_union_impl(std::floating_point auto pValue) : u_operand(pValue) {}
				~syntax_operand_union_impl();
			}			  _M_Impl;
			category_impl _M_Impl_Category;

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
		void _M_Impl_Init(meta::meta_object<T...>&);
		void _M_Impl_Init(std::integral		  auto);
		void _M_Impl_Init(std::floating_point auto);
		void _M_Impl_Init(meta::concepts::meta_operator auto&);
		template <std::size_t... Idx, typename V, typename... T>
		void _M_Impl_Init(meta::meta_operator<V, T...>&, std::index_sequence<Idx...>);
		template <std::size_t Idx, typename V, typename... T>
		void _M_Impl_Init(meta::meta_operator<V, T...>&);

	public:
		using name_type = name_type_impl;
		using category  = syntax_operand_impl::category_impl;

		template <typename V, typename... T>
		syntax_impl(meta::meta_operator<V, T...>&);

		
	};

	syntax_impl::syntax_operand_impl::syntax_operand_union_impl::syntax_operand_union_impl
		(meta::concepts::meta_operator auto& pOperator)
			: u_syntax(new syntax_impl(pOperator)) {}

	syntax_impl::syntax_operand_impl::syntax_operand_impl
		(meta::concepts::meta_operator auto& pOperator)
			: _M_Impl		  (pOperator),
			  _M_Impl_Category(category::syntax) {}

	template <typename... T>
	void
		syntax_impl::_M_Impl_Init
			(meta::meta_object<T...>& pMetaType) {
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
			: _M_Impl		  (pValue),
			  _M_Impl_Category(category::operand) {}

	syntax_impl::syntax_operand_impl::syntax_operand_impl
		(std::floating_point auto pValue)
			: _M_Impl		  (pValue),
			  _M_Impl_Category(category::operand) {}

	template <typename V, typename... T>
	syntax_impl::syntax_impl
		(meta::meta_operator<V, T...>& pMeta) {
			_M_Impl_Init(pMeta, std::make_index_sequence<sizeof...(T)>{});
	}

}