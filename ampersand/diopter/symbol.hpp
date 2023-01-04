#pragma once
#include <ampersand/diopter/type.hpp>

namespace ampersand::diopter {
	class symbol {
		using table_type_impl = std::unordered_map<type::name_type, type>;
			  table_type_impl _M_Table;

		template <std::size_t Idx, typename... T>
		bool _M_Table_Push_Impl(type&, meta::meta_type<T...>&);
		template <std::size_t... Idx, typename... T>
		bool _M_Table_Push_Impl(meta::meta_type<T...>&, std::index_sequence<Idx...>);
	public:
		using name_type  = type::name_type;
		using value_type = type;

		using		reference  =	   type&;
		using const_reference  = const type&;

		using		pointer = type*;
		using const_pointer = type*;

		symbol();

	public:
		template <typename... T>
		std::enable_if_t
			<std::conjunction_v
				<meta::utility::is_primitive_attribute<T>...>>
			push_symbol(meta::meta_type<T...>& pType) {
				_M_Table.insert
					(std::make_pair(pType.type_id(), type(pType)));
			}

		template <typename... T>
		std::enable_if_t
			<!std::conjunction_v
				<meta::utility::is_primitive_attribute<T>...>>
			push_symbol(meta::meta_type<T...>& pType) {
				_M_Table_Push_Impl
					(pType, std::make_index_sequence<sizeof...(T)>{});
			}

		type find_symbol(name_type);
		bool pop_symbol (name_type);
	};

	template <std::size_t Idx, typename... T>
	bool
		symbol::_M_Table_Push_Impl
			(type& pType, meta::meta_type<T...>& pMetaType) {
		auto  attr		= meta::get_attribute<Idx>(pMetaType);
		using attr_type = std::remove_reference_t<decltype(attr)>;

		if constexpr
			(!meta::utility::is_primitive_attribute_v<attr_type>) {
				auto attr_type_found = _M_Table.find(attr.type().type_id());
				if (attr_type_found == _M_Table.end())
					return false;
				else
					pType.link_type(attr.name(), (*attr_type_found).second);
					return true;
		}
		else
			return true;
	}

	template <std::size_t... Idx, typename... T>
	bool
		symbol::_M_Table_Push_Impl
			(meta::meta_type<T...>& pMeta, std::index_sequence<Idx...>) {
		type type_res	 (pMeta);
		bool type_success = true;
		((type_success = _M_Table_Push_Impl<Idx>(type_res, pMeta)), ...);

		if(type_success)
			_M_Table.insert
				(std::make_pair(pMeta.type_id(), type_res));

		return type_success;
	}
}