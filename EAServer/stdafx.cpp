// stdafx.cpp : 只包括标准包含文件的源文件
// EAServer.pch 将作为预编译标头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
#include <atlstr.h>

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用

char* wchar2char(wchar_t *wChar)
{
	size_t len = wcslen(wChar) + 1;
	size_t converted = 0;
	char *cChar;
	cChar = (char*)malloc(len * sizeof(char));
	wcstombs_s(&converted, cChar, len, wChar, _TRUNCATE);

	return cChar;
}