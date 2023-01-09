#pragma once
#include <ampersand/diopter/type.hpp>
#include <ampersand/diopter/type_compound.hpp>
#include <ampersand/diopter/type_compound_attr.hpp>
#include <ampersand/diopter/type_compound_nested.hpp>

#include <ampersand/diopter/type_function.hpp>
#include <ampersand/diopter/type_function_argument.hpp>

#include <ampersand/diopter/symbol_result.hpp>

#include <memory>

namespace ampersand::diopter {
	class symbol {
		using table_impl = std::unordered_map<type::name_type, std::shared_ptr<type>>;
		table_impl impl_symbol		   ,
				   impl_symbol_function;
		symbol*    impl_symbol_super;
		type	   impl_symbol_error { type::category::none };

		symbol_result impl_init_compound	   (compound&);
		symbol_result impl_init_compound_attr  (compound&);
		symbol_result impl_init_compound_nested(compound&);

		symbol_result impl_init_argument	   (function&);
		symbol_result impl_init_return		   (function&);
		symbol_result impl_init_class		   (function&);

		symbol_result impl_init_function	 (function&);
		symbol_result impl_init_method		 (function&);
		symbol_result impl_init_static_method(function&);

		static std::shared_ptr<type> impl_find_symbol		(symbol&, type::name_type);
		static std::shared_ptr<type> impl_find_symbol_global(symbol&, type::name_type);

		static std::shared_ptr<type> impl_find_function_symbol		 (symbol&, type::name_type);
		static std::shared_ptr<type> impl_find_function_symbol_global(symbol&, type::name_type);

	public:
		symbol();
		symbol(symbol&);
		using name_type = type::name_type;

	public:
		symbol_result push_symbol(meta::concepts::compound			 auto);
		symbol_result push_symbol(meta::concepts::function_type		 auto);
		symbol_result push_symbol(meta::concepts::method_type        auto);
		symbol_result push_symbol(meta::concepts::static_method_type auto);

		static type&  find_symbol				 (symbol&, name_type);
		static type&  find_symbol_global		 (symbol&, name_type);
		static type&  find_function_symbol	     (symbol&, name_type);
		static type&  find_function_symbol_global(symbol&, name_type);
	};

	symbol_result
		symbol::push_symbol
			(meta::concepts::compound auto pCompound) {
		compound*     sym_compound = new compound(pCompound);
		symbol_result sym_result   = impl_init_compound(*sym_compound);
		if (sym_result) {
			impl_symbol.insert
				(std::make_pair(pCompound.type_id(), std::shared_ptr<type>(sym_compound)));
			return sym_result;
		}
		else {
			delete sym_compound;
			return sym_result;
		}
	}


	symbol_result
		symbol::push_symbol
			(meta::concepts::function_type auto pFunction) {
		function*     sym_function = new function(pFuncntion);
		symbol_result sym_result   = impl_init_function(*sym_function);

		if (sym_result) {
			impl_symbol_function.insert
				(std::make_pair(pFunction.name(), std::shared_ptr<type>(sym_function)));
			return sym_result;
		}
		else {
			delete sym_function;
			return sym_result  ;
		}
	}

	symbol_result
		symbol::push_symbol
			(meta::concepts::method_type auto pMethod) {
		function*     sym_function = new function(pFuncntion);
		symbol_result sym_result   = impl_init_method(*sym_function);

		if (sym_result) {
			impl_symbol_function.insert
				(std::make_pair(pFunction.name(), std::shared_ptr<type>(sym_function)));
			return sym_result;
		}
		else {
			delete sym_function;
			return sym_result  ;
		}
	}

	symbol_result
		symbol::push_symbol
			(meta::concepts::static_method_type auto pMethod) {
		function*     sym_function = new function(pFuncntion);
		symbol_result sym_result   = impl_init_static_method(*sym_function);

		if (sym_result) {
			impl_symbol_function.insert
				(std::make_pair(pFunction.name(), std::shared_ptr<type>(sym_function)));
			return sym_result;
		}
		else {
			delete sym_function;
			return sym_result  ;
		}
	}
}