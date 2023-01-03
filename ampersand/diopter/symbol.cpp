#include "symbol.hpp"

namespace ampersand::diopter {
	symbol::type*
		symbol::find_symbol(const char* pName) {
			auto res = _M_Table.find(std::string(pName));
			return
				(res == _M_Table.end())
					? nullptr : &(*res).second;
	}

	symbol::type*
		symbol::find_symbol(meta::concepts::meta_type auto& pMeta) {
			return
				this->find_symbol(pMeta.type_name());
	}

	void  push_symbol(meta::concepts::meta_type auto&);
	void  pop_symbol(type&);
	void  pop_symbol(meta::concepts::meta_type auto&);
	void  pop_symbol(const char*);
}