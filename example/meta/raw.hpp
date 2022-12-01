#include <ampersand/meta/body/raw.hpp>

#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <iostream>

template <typename... AttrT>
auto
	example_raw_create
		(ampersand::meta::meta_type<AttrT...> pMeta) {
	return
		ampersand::meta::meta_object
			(ampersand::meta::body::raw{}, pMeta);
}

template
	<typename AttrT, typename ObjectT, typename ValueT>
void
	example_raw_set_value
		(ObjectT& pObj, AttrT, ValueT pValue) {
	pObj[AttrT{}] = pValue;
	std::cout << "[Raw][Object Set] Result : " << pObj[AttrT{}] << "\n";
}

template
	<typename AttrT, typename ObjectT>
void
	example_raw_get_value
		(ObjectT& pObj, AttrT) {
	std::cout << "[Raw][Object Get] Result : " << pObj[AttrT{}] << "\n";
}

template
	<typename AttrT, typename ObjectT>
void
	example_raw_get_address
		(ObjectT& pObj, AttrT) {
	std::cout << "[Raw][Object Address] Result : " << &pObj[AttrT{}] << "\n";
}