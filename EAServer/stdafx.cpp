// stdafx.cpp : 只包括标准包含文件的源文件
// EAServer.pch 将作为预编译标头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
#include <atlstr.h>

double GetLadder()
{
	if (step1 * ladder > 1 || step2 * ladder > 1) ladder = ladder * 0.001;
	return ladder;
}
DWORD GetStep1()
{
	step1 += 1;
	return step1;
}
DWORD GetStep2()
{
	step2 += 1;
	return step2;
}

char* wchar2char(wchar_t *wChar)
{
	size_t len = wcslen(wChar) + 1;
	size_t converted = 0;
	char *cChar;
	cChar = (char*)malloc(len * sizeof(char));
	wcstombs_s(&converted, cChar, len, wChar, _TRUNCATE);

	return cChar;
}

void PrintString(CString str)
{
	OutputDebugString(str.GetBuffer(str.GetLength()));
}
void PrintString(int num)
{
	PrintString((long)num);
}
void PrintString(long num)
{
	CString cs;
	cs.Format(_T("%d"), num);
	PrintString(cs);
}
void PrintString(double num)
{
	CString cs;
	cs.Format(_T("%f"), num);
	PrintString(cs);
}

int count(double *arr)
{
	return sizeof(arr) / sizeof(double);
}

// 以下是运算函数
double reverse_operation_a(double in, double a)
{
	if (in == 0) return 0;
	return a / in;
}

double positive_operation_a(double in, double a)
{
	return a * in;
}

double sum_all(int count, ...)
{
	if (count <= 0) return 0.0;

	double sum = 0;

	va_list arg_ptr;
	va_start(arg_ptr, count);

	for (int i = 0; i < count; i++)
	{
		sum += va_arg(arg_ptr, double);
	}

	va_end(arg_ptr);

	return sum;
}

double multiply_all(int count, ...)
{
	if (count <= 0) return 0.0;

	double sum = 1;

	va_list arg_ptr;
	va_start(arg_ptr, count);

	for (int i = 0; i < count; i++)
	{
		sum *= va_arg(arg_ptr, double);
	}

	va_end(arg_ptr);

	return sum;
}