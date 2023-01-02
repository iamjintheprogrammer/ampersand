#pragma once
#include <ampersand/meta/attribute.hpp>
#include <ampersand/meta/annotation.hpp>

#include <ampersand/meta/operator.hpp>
#include <ampersand/meta/verb.hpp>

#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/body_traits.hpp>

namespace ampersand::meta {
	template <typename MetaType>
	using meta_object = basic_meta_object<MetaType, body_traits<MetaType>>;
}