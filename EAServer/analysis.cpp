

#include "stdafx.h"

void tick(double *data) 
{
	CString cstr;

	cstr.Format(_T("hight:%f,bars:%d"), rates_m1.mqlRates[rates_m1.bars-1].high,
		rates_m1.bars);
	
	PrintString(cstr);
}