#pragma once
#include <ampersand/poly/poly_interface.hpp>
#include <ampersand/poly/poly_binary.hpp>

namespace ampersand::poly {
	template <typename... AnyType>
	class poly_object;

	template <typename... Attributes>
	class poly_object<poly_interface<meta::meta_type<Attributes...>>> {
		using    __string_type = std::string;
		using __interface_type = poly_interface<meta::meta_type<Attributes...>>;
		using   __operand_type = machine::operand;

		__interface_type& _M_Interface;
		__operand_type    _M_Operand  ;
		
	public:
		using string_type	 =    __string_type;
		using interface_type = __interface_type;

	public:
		poly_object(interface_type& pInterface, string_type pName)
			: _M_Interface(pInterface),
			  _M_Operand  (pInterface.name(), pName) {
			auto& cur_module = poly_binary::current();
				  cur_module.push_enter		   ();
				  cur_module.push_object_create(_M_Operand);
				  cur_module.push_leave	       ();
		}

		poly_object(interface_type& pInterface)
			: _M_Interface(pInterface),
			  _M_Operand  (pInterface.name(), "") {
			
		}

		~poly_object() {
			machine::operand::object op_this("", "");
			_M_Operand.get_operand(op_this);

			if (op_this.name().empty()) {
				auto& cur_module = poly_binary::current();
					  cur_module.push_leave();
			}
			else {
				auto& cur_module = poly_binary::current();
					  cur_module.push_enter();
					  cur_module.push_object_delete(_M_Operand);
					  cur_module.push_leave();
			}
		}

	public:
		template <typename Attr>
		typename Attr::value_type operator[](Attr) {
			machine::operand::object op_this  ("", "");
			machine::operand		 op_return("", ""),
									 op_key	  (_M_Interface[Attr{}].c_str());

			auto& cur_module = poly_binary::current();
				  cur_module.push_enter();
				  cur_module.push_object_reference
						(_M_Operand, op_return, op_key);
			
			return
				typename Attr::value_type{};
		}
	};

	template <typename... Attr, typename String>
	poly_object(poly_interface<meta::meta_type<Attr...>>, String)
		-> poly_object<poly_interface<meta::meta_type<Attr...>>>;
}