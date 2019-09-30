#include "HEString.h"
#include <comdef.h>

auto HEString::c2w(const char* str) -> const WCHAR* {
	const size_t cSize = strlen(str) + 1;
	auto* wc = new WCHAR[cSize];
	mbstowcs(wc, str, cSize);
	return wc;
}

auto HEString::w2c(const WCHAR* str) -> const char* {
	const _bstr_t b(str);
	return b;
}