

#include "stdafx.h"

#pragma comment(lib, "winmm.lib")

double forecast_for_rate(MqlRates rate)
{
	double dir = rate.open - rate.close;

	if (dir > 0) 
	{
		//todo
	}
	else if (dir < 0) 
	{
		//todo
	}
	else 
	{
		//todo
	}

	return dir;
}

double volume_analysis(double *data) 
{
	CString cs;

	cs.Format(_T("time is :::%d,成交：%.1f"), timeGetTime(), data[1]);

	PrintString(cs);

	return 100;
}

/***
 *  mqlRates数组索引越大数据越新
***/
int tick(double *data)
{
	CString cstr;

	MqlRates rate = rates_m1.mqlRates[rates_m1.bars-1];

	cstr.Format(_T("hight:%f,bars:%d"), rate.high, rates_m1.bars);
	
	PrintString(cstr);

	double aa = forecast_for_rate(rate);

	aa = volume_analysis(data);

	return (int)aa;
}