#include "desc_instruction.hpp"

using namespace ampersand::poly;
void(*invoke_describer_unit_table[])(decoder&, std::string&) = {
		nullptr,
		nullptr,

		& ampersand::poly::python::call		  ,
		& ampersand::poly::python::call_method,

		& ampersand::poly::python::ob_create   ,
		& ampersand::poly::python::ob_delete   ,
		& ampersand::poly::python::ob_reference,

		& ampersand::poly::python::op_add  ,
		& ampersand::poly::python::op_addeq,

		& ampersand::poly::python::op_sub  ,
		& ampersand::poly::python::op_subeq,

		& ampersand::poly::python::op_mul  ,
		& ampersand::poly::python::op_muleq,

		& ampersand::poly::python::op_div  ,
		& ampersand::poly::python::op_diveq,

		& ampersand::poly::python::move		   ,
		& ampersand::poly::python::move_shallow,
		& ampersand::poly::python::move_deep
};

namespace ampersand::poly::python {
void 
	call
		(decoder& pDecoder, std::string& pString) {
	pString += pDecoder.function_name();
	pString += "(";

	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args  ();

	++arg_begin;
	if (arg_begin != arg_end) {
		for ( ; arg_begin != arg_end; ++arg_begin)
			pString += (*arg_begin).name() + ",";
			pString.pop_back();
	}

	pString += ")";
}

void
	call_method
		(decoder& pDecoder, std::string& pString) {
	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args  ();

	++arg_begin;
	pString += (*arg_begin).name()		+ '.'
			+  pDecoder.function_name() + '(';

	++arg_begin;
	if (arg_begin != arg_end) {
		for ( ; arg_begin != arg_end; ++arg_begin)
			pString += (*arg_begin).name() + ",";
			pString.pop_back();
	}
	pString += ")";
}

void
	ob_create
		(decoder& pDecoder, std::string& pString) {
	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args();

	if ((*arg_begin).type_name().empty())
		return;

	if(!(*arg_begin).name().empty())
		pString += (*arg_begin).name() +  " = ";

	++arg_begin;
	pString += (*arg_begin).type_name() + '(';

	if (arg_begin != arg_end) {
		for (; arg_begin != arg_end; ++arg_begin)
			pString += (*arg_begin).name() + ",";
			pString.pop_back();
	}

	pString += ")";
}
void ob_delete   (decoder&, std::string&) {}
void
	ob_reference
		(decoder& pDecoder, std::string& pString) {
	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args  ();

	
	++arg_begin; pString += (*arg_begin).name() + '.';
	++arg_begin; pString += (*arg_begin).name();
}

void
	op_add
		(decoder& pDecoder, std::string& pString) {
	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args  ();

	++arg_begin; pString += (*arg_begin).name() + '+';
	++arg_begin; pString += (*arg_begin).name();
}

void
	op_addeq
		(decoder& pDecoder, std::string& pString) {
	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args  ();

	std::string front_str = (*arg_begin).name() + "+=";
	pString  = (front_str + pString);
}

void
	op_sub
		(decoder& pDecoder, std::string& pString) {
	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args  ();

	++arg_begin;
	pString += (*arg_begin++).name() + '-'
			+  (*arg_begin++).name();
}

void
	op_subeq
		(decoder& pDecoder, std::string& pString) {
	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args  ();

	std::string front_str = (*arg_begin).name() + "-=";
	pString  = (front_str + pString);
}

void
	op_mul
		(decoder& pDecoder, std::string& pString) {
	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args  ();

	++arg_begin;
	pString += (*arg_begin++).name() + '*'
			+  (*arg_begin++).name();
}

void
	op_muleq
		(decoder& pDecoder, std::string& pString) {
	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args  ();

	std::string front_str = (*arg_begin).name() + "*=";
	pString  = (front_str + pString);
}

void
	op_div
		(decoder& pDecoder, std::string& pString) {
	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args  ();

	++arg_begin;
	pString += (*arg_begin++).name() + '/'
			+  (*arg_begin++).name();
}

void
	op_diveq
		(decoder& pDecoder, std::string& pString) {
	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args  ();

	std::string front_str = (*arg_begin).name() + "/=";
	pString  = (front_str + pString);
}

void
	move
		(decoder& pDecoder, std::string& pString) {
	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args  ();

	std::string front_str = (*arg_begin++).name() 
						  + "="
						  + pString;

	pString = front_str;
}

void
	move_shallow
		(decoder& pDecoder, std::string& pString) {
	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args  ();

	std::string front_str = (*arg_begin++).name() 
						  + "="
						  + pString;

	pString = front_str;
}

void 
	move_deep
		(decoder& pDecoder, std::string& pString) {
	auto arg_begin = pDecoder.begin_args();
	auto arg_end   = pDecoder.end_args  ();

	std::string front_str = (*arg_begin).name()
						  + '='
						  + pString;

	pString = front_str;
}

void 
	invoke_describer_unit
		(instruction_verb pVerb, decoder& pDecoder, std::string& pString) {
	invoke_describer_unit_table[(std::uint32_t)pVerb]
		(pDecoder, pString);
}
}