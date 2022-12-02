#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <ampersand/meta/annotation.hpp>

namespace ampersand::schema {
	struct auto_increment : meta::annotation {};
	struct not_null		  : meta::annotation {};

	struct primary_key    : meta::annotation {};
	struct foreign_key    : meta::annotation {};
}