// EAServer.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define MT4_EXPFUNC __declspec(dllexport)

MT4_EXPFUNC double __stdcall SendInitData(MqlRates *rates, int len, int period)
{
	return(rates[0].low);
}

MT4_EXPFUNC double __stdcall SendTickData(double *data)
{
	SendData(data);
	return(data[0]);
}





