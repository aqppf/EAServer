// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#include <atlstr.h>
#include <atomic>

using namespace std;

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>
#include "stdarg.h"

#define PERIOD_M1	1
#define PERIOD_M5	5
#define PERIOD_M15	15
#define PERIOD_M30	30
#define PERIOD_H1	60
#define PERIOD_H4	240
#define PERIOD_D1	1440
#define PERIOD_W1	10080
#define PERIOD_MN1	43200

#pragma pack(push,1)
struct MqlRates
{
	__int64           ctm;
	double            open;
	double            high;
	double            low;
	double            close;
	unsigned __int64  vol_tick;
	int               spread;
	unsigned __int64  vol_real;
};
#pragma pack(pop)

struct MultiRates
{
	struct MqlRates* mqlRates;
	int bars;
	int period;
};

extern MultiRates rates_m1;
extern MultiRates rates_m5;
extern MultiRates rates_m15;
extern MultiRates rates_m30;
extern MultiRates rates_h1;
extern MultiRates rates_h4;
extern MultiRates rates_d1;
extern MultiRates rates_w1;
extern MultiRates rates_mn1;

extern atomic<double> ladder = 0.1;
extern atomic<DWORD> step1 = 1, step2 = 1;

double GetLadder();
DWORD GetStep1();
DWORD GetStep2();

void SendData(double *data);

char* wchar2char(wchar_t *wChar);

void PrintString(CString str);
void PrintString(int num);
void PrintString(long num);
void PrintString(double num);

int count(double *arr);

double sum_all(int count, ...);

double multiply_all(int count, ...);

double reverse_operation_a(double in, double a);

double positive_operation_a(double in, double a);



