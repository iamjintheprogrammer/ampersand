#include "symbol.hpp"

namespace ampersand::diopter {
	symbol::symbol()											{}
	symbol::symbol(symbol& pSuper) : impl_symbol_super(&pSuper) {}

	std::shared_ptr<type>
		symbol::impl_find_symbol
			(symbol& pSymbol, type::name_type pTypename) {
		for(auto it_symbol  = pSymbol.impl_symbol.begin();
				 it_symbol != pSymbol.impl_symbol.end  ();
			   ++it_symbol) {
			auto& pair_symbol = *it_symbol;

			if (pair_symbol.first == pTypename)
				return pair_symbol.second;

			compound* ptr_compound = static_cast<compound*>(pair_symbol.second.get());
			auto	  ptr_symbol   = compound::impl_find_type_from_all(*ptr_compound, pTypename);
			
			if (ptr_symbol) return ptr_symbol;
		}

		return std::shared_ptr<type> { nullptr };
	}

	std::shared_ptr<type>
		symbol::impl_find_symbol_global
			(symbol& pSymbol, type::name_type pTypename) {
		symbol* it_symbol = &pSymbol;

		while(it_symbol) {
			auto fnd_type_ptr = symbol::impl_find_symbol(*it_symbol, pTypename);
			if  (fnd_type_ptr)
				return fnd_type_ptr;

			it_symbol = it_symbol->impl_symbol_super;
		}

		return std::shared_ptr<type> { nullptr };
	}

	std::shared_ptr<type>
		symbol::impl_find_function_symbol
			(symbol& pSymbol, type::name_type pTypename) {
		for(auto it_symbol  = pSymbol.impl_symbol_function.begin();
				 it_symbol != pSymbol.impl_symbol_function.end  ();
			   ++it_symbol) {
			auto& pair_symbol = *it_symbol;

			if (pair_symbol.first == pTypename)
				return pair_symbol.second;
		}

		return std::shared_ptr<type> { nullptr };
	}

	std::shared_ptr<type>
		symbol::impl_find_function_symbol_global
			(symbol& pSymbol, type::name_type pTypename) {
		symbol* it_symbol = &pSymbol;

		while(it_symbol) {
			auto fnd_type_ptr = symbol::impl_find_function_symbol(*it_symbol, pTypename);
			if  (fnd_type_ptr)
				return fnd_type_ptr;

			it_symbol = it_symbol->impl_symbol_super;
		}

		return std::shared_ptr<type> { nullptr };
	}

	symbol_result
		symbol::impl_init_compound
			(compound& pCompound) {
		if (impl_symbol.find(pCompound.type_name()) != impl_symbol.end())
			return symbol_result(symbol_result::result_code::duplicated_declaration);

		symbol_result sym_result(symbol_result::result_code::success);

		sym_result = impl_init_compound_attr  (pCompound); if (!sym_result) return sym_result;
		sym_result = impl_init_compound_nested(pCompound); if (!sym_result) return sym_result;

		return sym_result;
	}

	symbol_result
		symbol::impl_init_compound_attr
			(compound& pCompound) {
		for(auto it_attr  = pCompound.impl_attribute.begin();
				 it_attr != pCompound.impl_attribute.end  ();
			   ++it_attr) {
			auto& attr_pair = *it_attr;
			if (attr_pair.second) continue;

			auto it_type_linked  = impl_symbol.find(attr_pair.first);
			if  (it_type_linked == impl_symbol.end())
				return symbol_result(symbol_result::result_code::attribute_symbol_not_found);

			auto& attr_type_linked = (*it_type_linked).second;
				  attr_pair.second = attr_type_linked;
		}

		return symbol_result(symbol_result::result_code::success);
	}

	symbol_result
		symbol::impl_init_compound_nested
			(compound& pCompound) {
		for(auto it_nested  = pCompound.impl_nested_declare.begin();
				 it_nested != pCompound.impl_nested_declare.end  ();
			   ++it_nested) {
			auto& pair_nested = *it_nested;
			if (pair_nested.second) continue;

			auto type_nested_ptr = symbol::impl_find_symbol_global(*this, pair_nested.first);
			if (!type_nested_ptr)
				return symbol_result(symbol_result::result_code::symbol_not_found);

			pair_nested.second = type_nested_ptr;
		}

		return symbol_result(symbol_result::result_code::success);
	}

	symbol_result
		symbol::impl_init_argument
			(function& pFunction) {
		for(auto it_arg  = pFunction.impl_argument.begin();
				 it_arg != pFunction.impl_argument.end  ();
			   ++it_arg) {
			auto& arg_pair = *it_arg;
			if (arg_pair.second) continue;

			auto arg_type = symbol::impl_find_symbol_global(*this, arg_pair.first);
			if (!arg_type)
				return symbol_result(symbol_result::result_code::argument_symbol_not_found);

			arg_pair.second = arg_type;
		}

		return symbol_result(symbol_result::result_code::success);
	}

	symbol_result
		symbol::impl_init_return
			(function& pFunction) {
		if(pFunction.impl_return.second)
			return symbol_result(symbol_result::result_code::success);

		auto ret_type = symbol::impl_find_symbol_global(*this, pFunction.impl_return.first);
		if (!ret_type)
			return symbol_result(symbol_result::result_code::argument_symbol_not_found);

		pFunction.impl_return.second = ret_type;
		return symbol_result(symbol_result::result_code::success);
	}

	symbol_result
		symbol::impl_init_class
			(function& pFunction) {
		if(pFunction.impl_class.second)
			return symbol_result(symbol_result::result_code::success);

		auto class_type = symbol::impl_find_symbol_global(*this, pFunction.impl_class.first);
		if (!class_type)
			return symbol_result(symbol_result::result_code::argument_symbol_not_found);

		pFunction.impl_class.second = class_type;
		return symbol_result(symbol_result::result_code::success);
	}

	symbol_result
		symbol::impl_init_function(function& pFunction) {
			symbol_result sym_res(symbol_result::result_code::success);

			sym_res = impl_init_return  (pFunction); if (!sym_res) return sym_res;
			sym_res = impl_init_argument(pFunction); if (!sym_res) return sym_res;

			return sym_res;
	}

	symbol_result
		symbol::impl_init_method(function& pFunction) {
			symbol_result sym_res(symbol_result::result_code::success);

			sym_res = impl_init_return  (pFunction); if (!sym_res) return sym_res;
			sym_res = impl_init_argument(pFunction); if (!sym_res) return sym_res;
			sym_res = impl_init_class   (pFunction); if (!sym_res) return sym_res;

			return sym_res;
	}

	symbol_result
		symbol::impl_init_static_method(function& pFunction) {
			symbol_result sym_res(symbol_result::result_code::success);

			sym_res = impl_init_return  (pFunction); if (!sym_res) return sym_res;
			sym_res = impl_init_argument(pFunction); if (!sym_res) return sym_res;
			sym_res = impl_init_class   (pFunction); if (!sym_res) return sym_res;

			return sym_res;
	}

	type&
		symbol::find_symbol
			(symbol& pSymbol, name_type pTypename) {
		auto sym_found = symbol::impl_find_symbol(pSymbol, pTypename);
		return
			(sym_found)
				? *sym_found : pSymbol.impl_symbol_error;
	}

	type&
		symbol::find_symbol_global
			(symbol& pSymbol, name_type pTypename) {
		auto sym_found = symbol::impl_find_symbol_global(pSymbol, pTypename);
		return
			(sym_found)
				? *sym_found : pSymbol.impl_symbol_error;
	}

	type&
		symbol::find_function_symbol
			(symbol& pSymbol, name_type pTypename) {
		auto sym_found = symbol::impl_find_function_symbol(pSymbol, pTypename);
		return
			(sym_found)
				? *sym_found : pSymbol.impl_symbol_error;
	}

	type&
		symbol::find_function_symbol_global
			(symbol& pSymbol, name_type pTypename) {
		auto sym_found = symbol::impl_find_function_symbol_global(pSymbol, pTypename);
		return
			(sym_found)
				? *sym_found : pSymbol.impl_symbol_error;
	}
}