// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

#pragma pack(push,1)
struct MqlRates
{
	__int64           ctm;
	double            open;
	double            low;
	double            high;
	double            close;
	unsigned __int64  vol_tick;
	int               spread;
	unsigned __int64  vol_real;
};
#pragma pack(pop)

void SendData(double *);

