#pragma once
#include <ampersand/meta.hpp>
#include <ampersand/diopter/engine/type_impl.hpp>

namespace ampersand::diopter {
	struct symbol_impl {
		using table_type = std::unordered_map<std::string, type_impl*>;
		table_type table;
	
		symbol_impl();

		template <typename... T> void push_symbol_impl(meta::meta_type<T...>&);
								 void  pop_symbol_impl(std::string);
						   type_impl* find_symbol_impl(std::string);
	};

	template <typename... T>
	void
		symbol_impl::push_symbol_impl
			(meta::meta_type<T...>& pMetaType) {
		bool	   res		   = true;
		type_impl* type_symbol = new type_impl(pMetaType.type_name());

		auto fn_init = [&] <std::size_t Idx>() {
			auto  attr	    = meta::get_attribute<Idx>(pMetaType);
			using attr_type = std::remove_reference_t<decltype(attr)>;
			
			if constexpr (meta::utility::is_primitive_attribute_v<attr_type>) {
				primitive_type_impl attr_type_impl;
				if constexpr (std::is_same_v<attr_type::>)

				type_symbol->u_type.u_complex.table.insert
					(std::make_pair(attr.name(), ))
			}

			auto attr_type = attr.type(); // May be Primitive or Complex Type

			if(table.find(std::string(attr_type.type_name()))
					!= table.end()) {
				res = false;
				return;
			}

			type_symbol->
		}
	}
}