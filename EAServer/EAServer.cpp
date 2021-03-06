// EAServer.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "analysis.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <atlstr.h>

#define MT4_EXPFUNC __declspec(dllexport)

MultiRates rates_m1;
MultiRates rates_m5;
MultiRates rates_m15;
MultiRates rates_m30;
MultiRates rates_h1;
MultiRates rates_h4;
MultiRates rates_d1;
MultiRates rates_w1;
MultiRates rates_mn1;

MT4_EXPFUNC double __stdcall SendInitData(MqlRates *rates, int bars, int period)
{
	CString cs;
	cs.Format(_T("PERIOD IS : %d"),period);
	PrintString(cs);

	switch (period)
	{
	case PERIOD_M1:
		rates_m1.mqlRates = rates;
		rates_m1.bars = bars;
		rates_m1.period = period;
		break;
	case PERIOD_M5:
		rates_m5.mqlRates = rates;
		rates_m5.bars = bars;
		rates_m5.period = period;
		break;
	case PERIOD_M15:
		rates_m15.mqlRates = rates;
		rates_m15.bars = bars;
		rates_m15.period = period;
		break;
	case PERIOD_M30:
		rates_m30.mqlRates = rates;
		rates_m30.bars = bars;
		rates_m30.period = period;
		break;
	case PERIOD_H1:
		rates_h1.mqlRates = rates;
		rates_h1.bars = bars;
		rates_h1.period = period;
		break;
	case PERIOD_H4:
		rates_h4.mqlRates = rates;
		rates_h4.bars = bars;
		rates_h4.period = period;
		break;
	case PERIOD_D1:
		rates_d1.mqlRates = rates;
		rates_d1.bars = bars;
		rates_d1.period = period;
	case PERIOD_W1:
		rates_w1.mqlRates = rates;
		rates_w1.bars = bars;
		rates_w1.period = period;
	case PERIOD_MN1:
		rates_mn1.mqlRates = rates;
		rates_mn1.bars = bars;
		rates_mn1.period = period;
		break;
	}
	
	return (double)(rates[bars-1].ctm);
}

MT4_EXPFUNC double __stdcall SendTickData(double *data)
{
	//SendData(data); // 发送到网络给其他平台处理

	tick(data);

	return(data[0]);
}





