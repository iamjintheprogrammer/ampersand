#pragma once
#include <ampersand/diopter/type_compound.hpp>
#include <ampersand/diopter/type_primitive.hpp>

namespace ampersand::diopter {
	class function : public type {
		friend class symbol;
		enum class  function_category_impl { function, method, static_method };
		using					 args_impl = std::unordered_map<type::name_type, std::shared_ptr<type>>;

		type	  impl_argument_error { type::category::none };
		args_impl impl_argument;
		
		std::pair<type::name_type, std::shared_ptr<type>>
			impl_return,
			impl_class ;

		function(meta::concepts::function_type      auto&);
		function(meta::concepts::method_type	    auto&);
		function(meta::concepts::static_method_type auto&);

		template <typename C, typename R, typename... Args> void impl_init(meta::meta_type<C, R(Args...)>   &);
		template <typename C, typename R, typename... Args> void impl_init(meta::meta_type<C, R(C, Args...)>&);
		template			 <typename R, typename... Args> void impl_init(meta::meta_type<R(Args...)>&);

		template <std::size_t... Idx> void impl_init(meta::concepts::function_type      auto&, std::index_sequence<Idx...>);
		template <std::size_t... Idx> void impl_init(meta::concepts::method_type	    auto&, std::index_sequence<Idx...>);
		template <std::size_t... Idx> void impl_init(meta::concepts::static_method_type auto&, std::index_sequence<Idx...>);

		void impl_do_arg_init(meta::concepts::compound  auto&);
		void impl_do_arg_init(meta::concepts::primitive auto&);

		void impl_do_ret_init(meta::concepts::compound  auto&);
		void impl_do_ret_init(meta::concepts::primitive auto&);

	public:
		class argument;

		using size_type			= args_impl::size_type;
		using name_type			= args_impl::key_type ;
		using function_category = function_category_impl;
	};

	function::function(meta::concepts::function_type      auto&);
	function::function(meta::concepts::method_type	    auto&);
	function::function(meta::concepts::static_method_type auto&);

	template <typename C, typename R, typename... Args>
	void
		function::impl_init
			(meta::meta_type<C, R(Args...)>& pMetaType) {
		impl_class = nullptr;
		impl_init(pMetaType, std::make_index_sequence<sizeof...(Args)>{});
	}

	template <typename C, typename R, typename... Args>
	void
		function::impl_init
			(meta::meta_type<C, R(C, Args...)>& pMetaType) {
		impl_class = nullptr;
		impl_init(pMetaType, std::make_index_sequence<sizeof...(Args)>{});
	}

	template <typename R, typename... Args>
	void
		function::impl_init
			(meta::meta_type<R(Args...)>& pMetaType) {
		impl_class = nullptr;
		impl_init(pMetaType, std::make_index_sequence<sizeof...(Args)>{});
	}

	template <std::size_t... Idx>
	void
		function::impl_init
			(meta::concepts::function_type auto& pMetaType, 
			 std::index_sequence<Idx...>) {
		  impl_do_ret_init(meta::get_return_type	   (pMetaType));
		((impl_do_arg_init(meta::get_argument_type<Idx>(pMetaType))), ...);
	}
	
	template <std::size_t... Idx>
	void
		function::impl_init
			(meta::concepts::method_type auto&, std::index_sequence<Idx...>) {
		  impl_do_ret_init(meta::get_return_type(pMetaType));
		((impl_do_arg_init(meta::get_argument_type<Idx>(pMetaType))), ...);
	}

	template <std::size_t... Idx>
	void
		function::impl_init
			(meta::concepts::static_method_type auto&, std::index_sequence<Idx...>) {
		  impl_do_ret_init(meta::get_return_type(pMetaType));
		((impl_do_arg_init(meta::get_argument_type<Idx>(pMetaType))), ...);
	}

	void
		function::impl_do_arg_init
			(meta::concepts::compound auto& pType) {
		impl_argument.insert
			(std::make_pair(pType.type_id(), std::shared_ptr<type>(nullptr)));
	}

	void
		function::impl_do_arg_init
			(meta::concepts::primitive auto& pType) {
		impl_argument.insert
			(std::make_pair(pType, std::shared_ptr<type>(new primitive(pType))));
	}

	void
		function::impl_do_ret_init
			(meta::concepts::compound auto& pType) {
		impl_return 
			= std::make_pair
				(pType.type_id(), std::shared_ptr<type>(nullptr));
	}

	void
		function::impl_do_ret_init
			(meta::concepts::primitive auto& pType) {
		impl_return 
			= std::make_pair
					(std::shared_ptr<type>(new primitive(pType)));
	}
}