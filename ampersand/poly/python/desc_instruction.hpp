#pragma once
#include <ampersand/poly/fetch.hpp>
#include <ampersand/poly/decoder.hpp>

namespace ampersand::poly::python {
	void call		 (decoder&, std::string&);
	void call_method (decoder&, std::string&);

	void ob_create   (decoder&, std::string&);
	void ob_delete   (decoder&, std::string&);
	void ob_reference(decoder&, std::string&);

	void op_add	     (decoder&, std::string&);
	void op_addeq	 (decoder&, std::string&);

	void op_sub	     (decoder&, std::string&);
	void op_subeq	 (decoder&, std::string&);

	void op_mul	     (decoder&, std::string&);
	void op_muleq	 (decoder&, std::string&);

	void op_div	     (decoder&, std::string&);
	void op_diveq	 (decoder&, std::string&);

	void move		 (decoder&, std::string&);
	void move_shallow(decoder&, std::string&);
	void move_deep   (decoder&, std::string&);

	void  invoke_describer_unit(instruction_verb, decoder&, std::string&);
}