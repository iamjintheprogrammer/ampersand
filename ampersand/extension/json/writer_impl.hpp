#pragma once
#include <json/json.h>
#include <ampersand/extension/json/types.hpp>

#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

namespace ampersand::extension::json {
	void
		__write_impl
			(Json::Value::iterator& pJson, std::int32_t& pWriteValue) {
		(*pJson) = pWriteValue;
	}

	void
		__write_impl
			(Json::Value::iterator& pJson, std::int64_t& pWriteValue) {
		(*pJson) = pWriteValue;
	}

	void
		__write_impl
			(Json::Value::iterator& pJson, std::uint32_t& pWriteValue) {
		(*pJson) = pWriteValue;
	}

	void
		__write_impl
			(Json::Value::iterator& pJson, std::uint64_t& pWriteValue) {
		(*pJson) = pWriteValue;
	}

	template <typename BodyT, typename... AttrT>
	void
		__write_impl
			(Json::Value& )
}