#include "script.hpp"

namespace ampersand::diopter {
	script::line& script::line::operator++() {
		++_M_Base;
		return *this;
	}

	script::line script::line::operator++(int) {
		++_M_Base;
		return *this;
	}

	syntax&
		script::line::operator*()
			{ return *_M_Base; }

	bool script::line::operator==(line& pLine) {
		return _M_Base == pLine._M_Base;
	}

	bool script::line::operator!=(line& pLine) {
		return _M_Base != pLine._M_Base;
	}

	script::line::line(script& pScript, bool pBegin) {
		_M_Base = (pBegin)
				? pScript._M_Impl_Syntax.begin()
				: pScript._M_Impl_Syntax.end  ();
	}

	script::line script::start_line() {
		return line(*this, true);
	}

	script::line script::end_line() {
		return line(*this, false);
	}
}