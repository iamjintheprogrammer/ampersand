#pragma once
#include <iostream>
#include <json/json.h>

#include <ampersand/extension/json/types.hpp>

#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

namespace ampersand::extension::json {

	void
		__read_impl
			(Json::Value::iterator& pJson, std::int32_t& pReadValue) {
		pReadValue = (*pJson).asInt();
	}

	void
		__read_impl
			(Json::Value::iterator& pJson, std::int64_t& pReadValue) {
		pReadValue = (*pJson).asInt64();
	}

	void
		__read_impl
			(Json::Value::iterator& pJson, std::uint32_t& pReadValue) {
		pReadValue = (*pJson).asUInt();
	}

	void
		__read_impl
			(Json::Value::iterator& pJson, std::uint64_t& pReadValue) {
		pReadValue = (*pJson).asUInt64();
	}

	template <typename BodyT, typename... AttrT>
	void
		__read_from
			(Json::Value&									 	  pValue,
			 meta::meta_object<BodyT, meta::meta_type<AttrT...>>& pObject) {
		auto json_iterator = pValue.begin();
	}
}