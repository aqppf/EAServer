

#include "stdafx.h"




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
	//todo

	return 100;
}

/***
 *  mqlRates��������Խ������Խ��
***/
int tick(double *data)
{
	CString cstr;

	MqlRates rate = rates_m1.mqlRates[rates_m1.bars-1];

	cstr.Format(_T("hight:%f,bars:%d"), rate.high, rates_m1.bars);
	
	PrintString(cstr);

	long aa = forecast_for_rate(rate);

	aa = volume_analysis(data);

	return aa;
}