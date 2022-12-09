#include "object.hpp"

namespace ampersand::poly::machine {
	format<format_category::create_object>::format
		(instruction& pInstruction) : format_base(pInstruction) {
		_M_Op_ArgIter
			= new argument_iterator(this->begin_args());
		_M_Op_Instance = &(**_M_Op_ArgIter); ++(*_M_Op_ArgIter);
	}

	format<format_category::create_object>::~format() {
		delete _M_Op_ArgIter;
	}

	format<format_category::create_object>::string_type
		format<format_category::create_object>::type_name() {
			operand::object				instance("", "");
			_M_Op_Instance->get_operand(instance);

			return instance.type_name();
	}

	format<format_category::create_object>::string_type
		format<format_category::create_object>::name() {
			operand::object				instance("", "");
			_M_Op_Instance->get_operand(instance);

			return instance.name();
	}

	format<format_category::create_object>::argument_iterator
		format<format_category::create_object>::argument_begin() {
			return *_M_Op_ArgIter;
	}

	format<format_category::create_object>::argument_iterator
		format<format_category::create_object>::argument_end() {
			return this->end_args();
	}

	format<format_category::delete_object>::format
		(instruction& pInstruction) : format_base(pInstruction) {
		_M_Op_ArgIter
			= new argument_iterator(this->begin_args());
		_M_Op_Instance = &(**_M_Op_ArgIter); ++(*_M_Op_ArgIter);
	}

	format<format_category::delete_object>::~format() {
		delete _M_Op_ArgIter;
	}

	format<format_category::delete_object>::string_type
		format<format_category::delete_object>::type_name() {
			operand::object				instance("", "");
			_M_Op_Instance->get_operand(instance);

			return instance.type_name();
	}

	format<format_category::delete_object>::string_type
		format<format_category::delete_object>::name() {
			operand::object				instance("", "");
			_M_Op_Instance->get_operand(instance);

			return instance.name();
	}

	format<format_category::reference_object>::format
		(instruction& pInstruction) : format_base(pInstruction) {
		_M_Op_ArgIter
			= new argument_iterator(this->begin_args());
		_M_Op_Instance = &(**_M_Op_ArgIter); ++(*_M_Op_ArgIter);
		_M_Op_Return   = &(**_M_Op_ArgIter); ++(*_M_Op_ArgIter);
		_M_Op_RefKey   = &(**_M_Op_ArgIter);
	}

	format<format_category::reference_object>::~format() {
		delete _M_Op_ArgIter;
	}

	format<format_category::reference_object>::string_type
		format<format_category::reference_object>::type_name() {
			operand::object				instance("", "");
			_M_Op_Instance->get_operand(instance);

			return instance.type_name();
	}

	format<format_category::reference_object>::string_type
		format<format_category::reference_object>::name() {
			operand::object				instance("", "");
			_M_Op_Instance->get_operand(instance);

			return instance.name();
	}

	operand&
		format<format_category::reference_object>::key() {
			return *_M_Op_RefKey;
	}

	operand&
		format<format_category::reference_object>::return_operand() {
			return *_M_Op_Return;
	}
}