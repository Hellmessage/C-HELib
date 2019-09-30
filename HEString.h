#ifndef HESTRING_H
#define HESTRING_H

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

class HEString {

public:
	static auto c2w(const char* str) -> const WCHAR*;
	static auto w2c(const WCHAR* str) -> const char*;
};




#endif