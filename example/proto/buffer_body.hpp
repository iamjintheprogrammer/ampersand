#pragma once

#include <iostream>
#include <ampersand/meta/body/raw.hpp>

#include <ampersand/proto/field.hpp>
#include <ampersand/proto/annotation.hpp>
#include <ampersand/proto/annotation_traits.hpp>

#include <ampersand/proto/buffer.hpp>
#include <ampersand/proto/body.hpp>

template <typename BufferT, typename ObjectT>
void
	example_import_packet
		(BufferT&& pBuffer, ObjectT&& pObject) {
	pBuffer = pObject;
}

template <typename BufferT>
void
	example_pseudo_receive
		(BufferT&& pBuffer) {
	using buffer_t = std::remove_const_t<std::remove_reference_t<BufferT>>;
	using namespace ampersand::proto;
	using namespace ampersand::meta::utility;

	if (has_annotated_attribute<buffer_t, is_remapped>::value)
		std::cout << "Have Field\n";

	std::cout << pBuffer[ampersand::proto::fields::field<int>] << std::endl;
}