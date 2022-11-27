#include <meta/field.hpp>
#include <meta/field_utility.hpp>
#include <meta/field_set.hpp>

static constexpr ampersand::meta::field<int, ampersand::meta::attribute_set<>> Field("Hello World");

void meta_add_attribute();
void meta_static_assert();