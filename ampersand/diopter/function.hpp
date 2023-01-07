#pragma once
#include <ampersand/diopter/condition.hpp>
#include <ampersand/diopter/loop.hpp>

#include <ampersand/diopter/syntax.hpp>
#include <ampersand/diopter/scope.hpp>

namespace ampersand::diopter {
	class function {
		enum class function_type_impl { function, method, static_method, none };
		function_type_impl  _M_Impl_Type	 ;
		object			    _M_Impl_Return	 ;
		std::vector<object> _M_Impl_Arguments;
		std::vector<syntax> _M_Impl_Syntax	 ;
		scope				_M_Impl_Scope    ;

		template <std::size_t... Idx>
		bool _M_Impl_Init_Syntax(meta::concepts::meta_script   auto&, std::index_sequence<Idx...>);
		bool _M_Impl_Init_Syntax(meta::concepts::meta_operator auto&);
		bool _M_Impl_Init_Syntax(meta::concepts::meta_type	   auto&);
		bool _M_Impl_Init_Syntax(meta::concepts::meta_object   auto&);
		
		template <std::size_t... Idx>
		bool _M_Impl_Init_Args(meta::concepts::meta_function	  auto&, std::index_sequence<Idx...>);
		template <std::size_t... Idx>
		bool _M_Impl_Init_Args(meta::concepts::meta_method		  auto&, std::index_sequence<Idx...>);
		template <std::size_t... Idx>
		bool _M_Impl_Init_Args(meta::concepts::meta_static_method auto&, std::index_sequence<Idx...>);
		bool _M_Impl_Init_Args(meta::concepts::meta_object		  auto&);
	public:
		function();
		template <typename R, typename... Args, typename... Scripts>
		function(scope, meta::meta_function<R(Args...), meta::meta_script<Scripts...>>&);
		template <typename C, typename R, typename... Args, typename... Scripts>
		function(scope, meta::meta_function<C, R(C, Args...), meta::meta_script<Scripts...>>&);
		template <typename C, typename R, typename... Args, typename... Scripts>
		function(scope, meta::meta_function<C, R(Args...), meta::meta_script<Scripts...>>&);

	public:
						 operator bool()		   ;
		object		get_return_value  ()		   ;
		object		get_argument      (std::size_t);
		std::size_t get_argument_count()		   ;
		syntax      get_syntax	      (std::size_t);
		std::size_t get_syntax_count  ()		   ;
	};

	bool
		function::_M_Impl_Init_Syntax
			(meta::concepts::meta_operator auto& pOperator) {
		_M_Impl_Syntax.emplace_back(pOperator);
	}

	bool
		function::_M_Impl_Init_Syntax
			(meta::concepts::meta_type auto& pMetaType) {
		_M_Impl_Scope.get_scoped_symbol().push_symbol(pMetaType);
	}

	bool
		function::_M_Impl_Init_Syntax
			(meta::concepts::meta_object auto& pMetaObject) {
		using meta_object_type = std::remove_reference_t<decltype(pMetaObject)>;
		
		if constexpr
			(meta::utility::is_primitive_type_v<meta_object_type>) {
				type   ob_type  (pMetaObject.type_of());
				object ob_entity(object::category::dynamic, pMetaObject.name(), ob_type);

				_M_Impl_Scope.get_scoped_stack().push_object(ob_entity);
		}
		else {
			type ob_type
				= _M_Impl_Scope.find_scoped_symbol
						(pMetaObject.type_of().type_of().type_id());
			if(!ob_type)
				ob_type
					= _M_Impl_Scope.find_scoped_symbol
						(pMetaObject.type_of().type_of().type_id());
			if (!ob_type)
				return false; // Cannot Find Symbol.
			
			object ob_entity
				(object::category::dynamic, pMetaObject.name(), ob_type);
			return
				_M_Impl_Scope.get_scoped_stack().push_object
					(ob_entity);
		}

		
		return true;
	}

	template <std::size_t... Idx>
	bool
		_M_Impl_Init_Syntax
			(meta::concepts::meta_script auto& pScript,
				std::index_sequence<Idx...>) {
		bool init_res = true;
		((init_res = _M_Impl_Init_Syntax(meta::get_script_element<Idx>(pScript))), ...);

		return init_res;
	}

	template <std::size_t... Idx>
	bool
		function::_M_Impl_Init_Args
			(meta::concepts::meta_function auto& pFunc, std::index_sequence<Idx...>) {
		bool init_res = true;
		((init_res = _M_Impl_Init_Args(meta::get_argument_value<Idx>(pFunc))), ...);

		return init_res;
	}

	template <std::size_t... Idx>
	bool
		function::_M_Impl_Init_Args
			(meta::concepts::meta_method auto& pFunc, std::index_sequence<Idx...>) {
		bool init_res = true;
		((init_res = _M_Impl_Init_Args(meta::get_argument_value<Idx>(pFunc))), ...);

		return init_res;
	}

	template <std::size_t... Idx>
	bool
		function::_M_Impl_Init_Args
			(meta::concepts::meta_static_method auto& pFunc, std::index_sequence<Idx...>) {
		bool init_res = true;
		((init_res = _M_Impl_Init_Args(meta::get_argument_value<Idx>(pFunc))), ...);

		return init_res;
	}

	bool
		function::_M_Impl_Init_Args
			(meta::concepts::meta_object auto& pObject) {
		type ob_type
				= _M_Impl_Scope.find_scoped_symbol(pObject);
		if(!ob_type)
			ob_type
				= _M_Impl_Scope.find_global_symbol(pObject);

		if(!ob_type)
			return false; // Cannot Find Symbol for object.

		object ob_entity(object::category::dynamic, pObject.name(), ob_type);
		
		_M_Impl_Arguments.push_back					(ob_entity);
		_M_Impl_Scope.get_scoped_stack().push_object(ob_entity);

		return true;
	}

	template <typename R, typename... Args, typename... Scripts>
	function::function
		(scope pScope, 
			meta::meta_function<R(Args...), meta::meta_script<Scripts...>>& pFunc)
				: _M_Impl_Type(function_type_impl::function) {
		_M_Impl_Init_Syntax(pFunc, std::make_index_sequence<sizeof...(Scripts)>{});
		_M_Impl_Init_Args  (pFunc, std::make_index_sequence<sizeof...(Args)>   {});

		type ret_type
				= _M_Impl_Scope.find_scoped_symbol(pObject);
		if(!ret_type)
			ret_type
				= _M_Impl_Scope.find_global_symbol(pObject);

		if(!ret_type)
			return; // Cannot Find Symbol for object.

		object 
			ret_entity
				(object::category::dynamic,
					pFunc.get_return_value().name(),
						ret_type);
		_M_Impl_Return = ret_entity;

	}
	template <typename C, typename R, typename... Args, typename... Scripts>
	function::function
		(scope pScope,
			meta::meta_function<C, R(C, Args...), meta::meta_script<Scripts...>>& pFunc)
				: _M_Impl_Type(function_type_impl::method) {
		_M_Impl_Init_Syntax(pFunc, std::make_index_sequence<sizeof...(Scripts)>{});
		_M_Impl_Init_Args  (pFunc, std::make_index_sequence<sizeof...(Args)>   {});

		type ret_type
				= _M_Impl_Scope.find_scoped_symbol(pObject);
		if(!ret_type)
			ret_type
				= _M_Impl_Scope.find_global_symbol(pObject);

		if(!ret_type)
			return; // Cannot Find Symbol for object.

		object 
			ret_entity
				(object::category::dynamic,
					pFunc.get_return_value().name(),
						ret_type);
		_M_Impl_Return = ret_entity;
	}

	template <typename C, typename R, typename... Args, typename... Scripts>
	function::function
		(scope pScope, 
			meta::meta_function<C, R(Args...), meta::meta_script<Scripts...>>& pFunc)
				: _M_Impl_Type(function_type_impl::static_method) {
		_M_Impl_Init_Syntax(pFunc, std::make_index_sequence<sizeof...(Scripts)>{});
		_M_Impl_Init_Args  (pFunc, std::make_index_sequence<sizeof...(Args)>   {});

		type ret_type
				= _M_Impl_Scope.find_scoped_symbol(pObject);
		if(!ret_type)
			ret_type
				= _M_Impl_Scope.find_global_symbol(pObject);

		if(!ret_type)
			return; // Cannot Find Symbol for object.

		object 
			ret_entity
				(object::category::dynamic,
					pFunc.get_return_value().name(),
						ret_type);
		_M_Impl_Return = ret_entity;
	}

namespace utility {
	template <typename AnyType>
	struct is_function		     : std::false_type {};
	template <>
	struct is_function<function> : std::true_type  {};
	template <typename AnyType>
	inline constexpr bool is_function_v = is_function<AnyType>::value;
}

namespace concepts {
	template <typename AnyType>
	concept function = utility::is_function_v<AnyType>;
}
}