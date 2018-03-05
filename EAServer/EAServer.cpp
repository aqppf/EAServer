// EAServer.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define MT4_EXPFUNC __declspec(dllexport)

#pragma pack(push,1)
struct RateInfo
{
	__int64           ctm;
	double            open;
	double            low;
	double            high;
	double            close;
	unsigned __int64  vol_tick;
};
#pragma pack(pop)

MT4_EXPFUNC double __stdcall SendInitData(RateInfo* rates, int len, int period)
{
	return(23.256);
}

MT4_EXPFUNC double __stdcall test(int len)
{
	return(8888.2225888);
}

MT4_EXPFUNC double __stdcall SendTickData(double *data)
{
	SendData(data);
	return(data[0]);
}





