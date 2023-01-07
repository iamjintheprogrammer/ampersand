#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <ampersand/meta/operator.hpp>

#include <ampersand/meta/meta_script.hpp>

namespace ampersand::meta {
	template <typename... AnyType>
	class meta_function;

	template
		<concepts::meta_object R,
			concepts::meta_object... Args,
				concepts::meta_script Script>
	class meta_function<R(Args...), Script> {
		using name_type_impl   = std::string_view;
		using script_type_impl = Script;

		using	 return_type_impl = R;
		using argument_tuple_impl = std::tuple<Args...>;

		  name_type_impl _M_Impl_Name  ;
		script_type_impl _M_Impl_Script;

		   return_type_impl _M_Impl_Return;
		argument_tuple_impl _M_Impl_Argument;
	public:
		using   name_type = name_type_impl;
		using script_type = script_type_impl;

		using return_type = return_type_impl;

		meta_function(name_type, script_type, R, Args...);
		meta_function			(script_type, R, Args...);

		return_type& get_return_value()				 { return _M_Impl_Return; }
		script_type& get_script		 ()			     { return _M_Impl_Script; }
		auto			   operator()(Args... pArgs) { 
			return
				meta_operator
					{ invoke{}, *this, _M_Impl_Return, pArgs... };
		}
		template <std::size_t Idx, typename... T>
		friend auto& get_argument_value(meta_function<T...>&);
	};

	template
		<concepts::meta_type C,
			concepts::meta_object    R,
			concepts::meta_object... Args,
				concepts::meta_script Script>
	class meta_function<C, R(C, Args...), Script> { // Method
		using   name_type_impl = std::string_view;
		using script_type_impl = Script;
		using  class_type_impl = C;

		using	 return_type_impl = R;
		using argument_tuple_impl = std::tuple<Args...>;

		     name_type_impl _M_Impl_Name    ;
		   script_type_impl _M_Impl_Script  ;

		   return_type_impl _M_Impl_Return  ;
		argument_tuple_impl _M_Impl_Argument;
		    class_type_impl _M_Impl_Class   ;
	public:
		using   name_type = name_type_impl;
		using script_type = script_type_impl;

		using return_type = return_type_impl;
		using  class_type =  class_type_impl;

		meta_function(name_type, script_type, class_type, R, Args...);
		meta_function			(script_type, class_type, R, Args...);

		return_type& get_return_value()				 { return _M_Impl_Return; }
		script_type& get_script		 ()				 { return _M_Impl_Script; }
		class_type&  get_class		 ()			     { return _M_Impl_Class;  }
		auto			   operator()(Args... pArgs) {
			return
				meta_operator
					{ invoke_method{}, *this, _M_Impl_Return, _M_Impl_Class, pArgs... };
		}

		template <std::size_t Idx, typename... T>
		friend auto& get_argument_value(meta_function<T...>&);
	};

	template
		<concepts::meta_type C,
			concepts::meta_object    R,
			concepts::meta_object... Args,
				concepts::meta_script Script>
	class meta_function<C, R(Args...), Script> { // Method
		using   name_type_impl = std::string_view;
		using script_type_impl = Script;
		using  class_type_impl = C;

		using	 return_type_impl = R;
		using argument_tuple_impl = std::tuple<Args...>;

		  name_type_impl _M_Impl_Name  ;
		script_type_impl _M_Impl_Script;

		   return_type_impl _M_Impl_Return  ;
		argument_tuple_impl _M_Impl_Argument;
		    class_type_impl _M_Impl_Class   ;
	public:
		using   name_type = name_type_impl;
		using script_type = script_type_impl;

		using return_type = return_type_impl;
		using  class_type =  class_type_impl;

		meta_function(name_type, script_type, class_type, R, Args...);
		meta_function			(script_type, class_type, R, Args...);

		constexpr return_type& get_return_value()			   { return _M_Impl_Return; }
		constexpr script_type& get_script	   ()			   { return _M_Impl_Script; }
		class_type&			   get_class	   ()			   { return _M_Impl_Class;  }
		auto						 operator()(Args... pArgs) {
			return
				meta_operator
					{ invoke_static_method{}, *this, _M_Impl_Return, pArgs... };
		}

		template <std::size_t Idx, typename... T>
		friend auto&	   get_argument_value(meta_function<T...>&);
		template <typename... T>
		friend std::size_t get_argument_count(meta_function<T...>&);
	};

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
		(name_type pName, script_type pScript, R pReturn, Arg... pArgs)
			: _M_Impl_Name    (pName)  ,
		      _M_Impl_Script  (pScript),
			  _M_Impl_Return  (pReturn),
			  _M_Impl_Argument(pArgs...) {}

	template
		<concepts::meta_object R,
			concepts::meta_object... Arg ,
				concepts::meta_script Script>
	meta_function<R(Arg...), Script>::meta_function
		(script_type pScript, R pReturn, Arg... pArgs)
			: _M_Impl_Name    (nullptr),
		      _M_Impl_Script  (pScript),
			  _M_Impl_Return  (pReturn),
			  _M_Impl_Argument(pArgs...) {}

	template
		<concepts::meta_type C,
			concepts::meta_object    R,
			concepts::meta_object... Args,
				concepts::meta_script Script>
	meta_function<C, R(C, Args...), Script>::meta_function
		(name_type   pName  ,
		 script_type pScript,
		 class_type  pClass ,
		 R		     pReturn,
		 Args...	 pArgs) : _M_Impl_Name    (pName)  ,
							  _M_Impl_Script  (pScript),
							  _M_Impl_Return  (pReturn),
							  _M_Impl_Argument(pArgs...) {}

	template
		<concepts::meta_type C,
			concepts::meta_object    R,
			concepts::meta_object... Args,
				concepts::meta_script Script>
	meta_function<C, R(C, Args...), Script>::meta_function
		(script_type pScript,
		 class_type  pClass ,
		 R		     pReturn,
		 Args...	 pArgs) : _M_Impl_Name    (nullptr),
							  _M_Impl_Script  (pScript),
							  _M_Impl_Return  (pReturn),
							  _M_Impl_Argument(pArgs...) {}

	template
		<concepts::meta_type C,
			concepts::meta_object    R,
			concepts::meta_object... Args,
				concepts::meta_script Script>
	meta_function<C, R(Args...), Script>::meta_function
		(name_type   pName  ,
		 script_type pScript,
		 class_type  pClass ,
		 R		     pReturn,
		 Args...	 pArgs) : _M_Impl_Name    (pName)  ,
							  _M_Impl_Script  (pScript),
							  _M_Impl_Return  (pReturn),
							  _M_Impl_Argument(pArgs...) {}

	template
		<concepts::meta_type C,
			concepts::meta_object    R,
			concepts::meta_object... Args,
				concepts::meta_script Script>
	meta_function<C, R(Args...), Script>::meta_function
		(script_type pScript,
		 class_type  pClass ,
		 R		     pReturn,
		 Args...	 pArgs) : _M_Impl_Name    (nullptr),
							  _M_Impl_Script  (pScript),
							  _M_Impl_Return  (pReturn),
							  _M_Impl_Argument(pArgs...) {}
}

namespace ampersand::meta::utility {
	template <typename AnyType>
	struct is_meta_function							   : std::false_type {};
	template <typename... AnyType>
	struct is_meta_function<meta_function<AnyType...>> : std::true_type  {};
	template <typename AnyType>
	inline constexpr bool is_meta_function_v = is_meta_function<AnyType>::value;

	template <typename AnyType>
	struct is_meta_dynamic_method											   : std::false_type {};
	template <typename C, typename R, typename... Args, typename... AnyType>
	struct is_meta_dynamic_method<meta_function<C, R(C, Args...), AnyType...>> : std::true_type  {};
	template <typename AnyType>
	inline constexpr bool is_meta_dynamic_method_v = is_meta_dynamic_method<AnyType>::value;

	template <typename AnyType>
	struct is_meta_static_method							: std::false_type {};
	template <typename... AnyType>
	struct is_meta_static_method<meta_function<AnyType...>> : std::true_type  {};
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