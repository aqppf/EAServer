// EAServer.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <atlstr.h>

#define MT4_EXPFUNC __declspec(dllexport)


MT4_EXPFUNC double __stdcall SendInitData(MqlRates* rates, int length, int period)
{
	int i = length;
	CString STemp;
	STemp.Format(_T("%.5f,%.5f,%.5f,%.5f,%d"), rates[i].open, rates[i].close, 
		rates[i].high, rates[i].low, length);
	MessageBox(0, STemp, 0, 0);
	return(rates[i].ctm);
}

MT4_EXPFUNC double __stdcall SendTickData(double *data)
{
	SendData(data);
	return(data[0]);
}





