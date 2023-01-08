#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <ampersand/meta/operator.hpp>

#include <ampersand/meta/meta_script.hpp>

namespace ampersand::meta {
	template <typename... AnyType>
	class meta_function;

	template
		<concepts::meta_object R, concepts::meta_object... Args, concepts::meta_script Script>
	class meta_function<R(Args...), Script> {
		using    script_type_impl = Script;
		using	 return_type_impl = R;
		using argument_tuple_impl = std::tuple<Args...>;
		using	        type_impl = meta_type<typename R::type(typename Args::type...)>;

		   script_type_impl _M_Impl_Script  ;
		   return_type_impl _M_Impl_Return  ;
		argument_tuple_impl _M_Impl_Argument;
				  type_impl _M_Impl_Type	;
	public:
		using script_type = script_type_impl;
		using	     type =		   type_impl;
		using return_type = return_type_impl;

		constexpr meta_function(const char*, script_type, R, Args...);
		constexpr meta_function			    (script_type, R, Args...);

		type				  type_of() { return _M_Impl_Type  ; }
		return_type& get_return_value() { return _M_Impl_Return; }
		script_type& get_script		 () { return _M_Impl_Script; }


		template <std::size_t Idx, typename... T>
		friend auto& get_argument_value(meta_function<T...>&);
	};

	template <concepts::meta_script Script, concepts::meta_object R, concepts::meta_object... Args>
	meta_function(const char*, Script, R, Args...)
		-> meta_function<R(Args...), Script>;
	template <concepts::meta_script Script, concepts::meta_object R, concepts::meta_object... Args>
	meta_function(Script, R, Args...)
		-> meta_function<R(Args...), Script>;

	template
		<concepts::meta_type C,
			concepts::meta_object R, concepts::meta_object... Args, concepts::meta_script Script>
	class meta_function<C, R(C, Args...), Script> { // Method
		using script_type_impl = Script;
		using  class_type_impl = C;

		using	 return_type_impl = R;
		using argument_tuple_impl = std::tuple<Args...>;
		using		    type_impl = meta_type<C, typename R::type(C, typename Args::type...)>;

				  type_impl _M_Impl_Type	;
		   script_type_impl _M_Impl_Script  ;
		   return_type_impl _M_Impl_Return  ;
		argument_tuple_impl _M_Impl_Argument;
	public:
		using script_type = script_type_impl;
		using		 type =		   type_impl;
		using return_type = return_type_impl;
		using  class_type =  class_type_impl;

		constexpr meta_function(const char*, script_type, R, class_type, Args...);

		type				  type_of() { return _M_Impl_Type  ; }
		return_type& get_return_value() { return _M_Impl_Return; }
		script_type& get_script		 () { return _M_Impl_Script; }

		template <std::size_t Idx, typename... T>
		friend auto& get_argument_value(meta_function<T...>&);
	};

	template <concepts::meta_script Script, concepts::meta_type C, concepts::meta_object R, concepts::meta_object... Args>
	meta_function(const char*, Script, R, C, Args...)
		-> meta_function<C, R(C, Args...), Script>;
	template <concepts::meta_script Script, concepts::meta_type C, concepts::meta_object R, concepts::meta_object... Args>
	meta_function(Script, R, C, Args...)
		-> meta_function<C, R(C, Args...), Script>;

	template
		<concepts::meta_type C,
			concepts::meta_object R, concepts::meta_object... Args, concepts::meta_script Script>
	class meta_function<C, R(Args...), Script> { // Method
		using script_type_impl = Script;
		using  class_type_impl = C;
		using		 type_impl = meta_type<C, typename R::type(typename Args::type...)>;

		using	 return_type_impl = R;
		using argument_tuple_impl = std::tuple<Args...>;

				  type_impl _M_Impl_Type	;
		   script_type_impl _M_Impl_Script  ;
		   return_type_impl _M_Impl_Return  ;
		argument_tuple_impl _M_Impl_Argument;
	public:
		using        type =		   type_impl;
		using script_type = script_type_impl;

		using return_type = return_type_impl;
		using  class_type =  class_type_impl;

		constexpr meta_function(const char*, script_type, class_type, R, Args...);

		type				  type_of() { return _M_Impl_Type  ; }
		return_type& get_return_value() { return _M_Impl_Return; }
		script_type& get_script	     () { return _M_Impl_Script; }

		template <std::size_t Idx, typename... T>
		friend auto& get_argument_value(meta_function<T...>&);
	};

	template <concepts::meta_script Script, concepts::meta_type C, concepts::meta_object R, concepts::meta_object... Args>
	meta_function(const char*, Script, C, R, Args...)
		-> meta_function<C, R(Args...), Script>;
	template <concepts::meta_script Script, concepts::meta_type C, concepts::meta_object R, concepts::meta_object... Args>
	meta_function(Script, C, R, Args...)
		-> meta_function<C, R(Args...), Script>;

	template <std::size_t Idx, typename... T>
	auto&
		get_argument_value
			(meta_function<T...>& pMetaFunction) {
		return
			std::get<Idx>(pMetaFunction._M_Impl_Argument);
	}

	template
		<concepts::meta_object R,
			concepts::meta_object... Arg ,
				concepts::meta_script Script>
	meta_function<R(Arg...), Script>::meta_function
		(const char* pName, script_type pScript, R pReturn, Arg... pArgs)
			: _M_Impl_Type    (pName)  ,
		      _M_Impl_Script  (pScript),
			  _M_Impl_Return  (pReturn),
			  _M_Impl_Argument(pArgs...) {}

	template
		<concepts::meta_object R,
			concepts::meta_object... Arg ,
				concepts::meta_script Script>
	meta_function<R(Arg...), Script>::meta_function
		(script_type pScript, R pReturn, Arg... pArgs)
			: _M_Impl_Type    ()	   ,
		      _M_Impl_Script  (pScript),
			  _M_Impl_Return  (pReturn),
			  _M_Impl_Argument(pArgs...) {}

	template
		<concepts::meta_type C,
			concepts::meta_object    R,
			concepts::meta_object... Args,
				concepts::meta_script Script>
	meta_function<C, R(C, Args...), Script>::meta_function
		(const char* pName  ,
		 script_type pScript,
		 R		     pReturn,
		 class_type  pClass ,
		 Args...	 pArgs) : _M_Impl_Type    (pName, pClass),
							  _M_Impl_Script  (pScript)		 ,
							  _M_Impl_Return  (pReturn)		 ,
							  _M_Impl_Argument(pArgs...)	 {  }

	template
		<concepts::meta_type C,
			concepts::meta_object    R,
			concepts::meta_object... Args,
				concepts::meta_script Script>
	meta_function<C, R(Args...), Script>::meta_function
		(const char* pName  ,
		 script_type pScript,
		 class_type  pClass ,
		 R		     pReturn,
		 Args...	 pArgs) : _M_Impl_Type    (pName, pClass),
							  _M_Impl_Script  (pScript)		 ,
							  _M_Impl_Return  (pReturn)		 ,
							  _M_Impl_Argument(pArgs...)	 {  }
}

namespace ampersand::meta::utility {
	template <typename AnyType>
	struct is_meta_function									   : std::false_type {};
	template
		<concepts::meta_object R,
			concepts::meta_object... Args, concepts::meta_script Script>
	struct is_meta_function<meta_function<R(Args...), Script>> : std::true_type {};
	template <typename AnyType>
	inline constexpr bool is_meta_function_v = is_meta_function<AnyType>::value;

	template <typename AnyType>
	struct is_meta_dynamic_method											   : std::false_type {};
	template
		<concepts::meta_type C,
			concepts::meta_object R, concepts::meta_object... Args,
				concepts::meta_script Script>
	struct is_meta_dynamic_method<meta_function<C, R(C, Args...), Script>> : std::true_type  {};
	template <typename AnyType>
	inline constexpr bool is_meta_dynamic_method_v = is_meta_dynamic_method<AnyType>::value;

	template <typename AnyType>
	struct is_meta_static_method							: std::false_type {};
	template
		<concepts::meta_type C,
			concepts::meta_object R, concepts::meta_object... Args,
				concepts::meta_script Script>
	struct is_meta_static_method<meta_function<C, R(Args...), Script>> : std::true_type  {};
	template <typename AnyType>
	inline constexpr bool is_meta_static_method_v = is_meta_static_method<AnyType>::value;

	template <typename AnyType>
	struct is_meta_method
		: std::disjunction
			<
				is_meta_dynamic_method<AnyType>,
				is_meta_static_method <AnyType>
			> {};

	template <typename AnyType>
	inline constexpr bool is_meta_method_v = is_meta_method<AnyType>::value;
}

namespace ampersand::meta::concepts {
	template <typename AnyType>
	concept meta_function	    = utility::is_meta_function_v	   <AnyType>;

	template <typename AnyType>
	concept meta_dynamic_method = utility::is_meta_dynamic_method_v<AnyType>;

	template <typename AnyType>
	concept meta_static_method  = utility::is_meta_static_method_v <AnyType>;

	template <typename AnyType>
	concept meta_method			= utility::is_meta_method_v		   <AnyType>;
}