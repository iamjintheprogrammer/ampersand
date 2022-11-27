#include <meta/field.hpp>
#include <meta/field_utility.hpp>

static constexpr ampersand::meta::field<int, ampersand::meta::attribute_set<>> Field("Hello World");

void example_meta_add_attribute();
void example_meta_constexpr    ();