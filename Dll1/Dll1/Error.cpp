#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include "Error.h"
#include <string>
#include "Define.h"

using namespace std;

void Error::finish(const char * errorMessage, const char* lpszFuncName, int lineN)
{
	char funcName[1024];
	sprintf(funcName, "%s", lpszFuncName);
	printf("Error.cpp‚æ‚è\n%s\n%s(%d)"
		, errorMessage
		, funcName
		, lineN
	);
	exit(99);
}