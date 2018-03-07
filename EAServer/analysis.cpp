

#include "stdafx.h"
#include <atlstr.h>

void test() 
{
	CString cstr;

	cstr.Format(_T("test okokok %f"), rates_m15.mqlRates[rates_m15.bars-1].high);
	

	MessageBox(0, cstr, 0, 0);
}