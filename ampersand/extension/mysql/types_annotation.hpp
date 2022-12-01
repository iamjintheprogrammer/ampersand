#pragma once
#include <ampersand/meta/annotation.hpp>

namespace ampersand::extension::mysql::annotation {
	struct auto_increment : meta::annotation {};
	struct not_null		  : meta::annotation {};

	struct primary_key    : meta::annotation {};
	struct foreign_key    : meta::annotation {};
}