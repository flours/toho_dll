#pragma once
#include <Windows.h>

class Error
{
public:
	static void finish(const char* errorMessage, const char* lpszFuncName, int lineN);
};