

#include "stdafx.h"
#include "analysis.h"
#include <time.h>

#pragma comment(lib, "winmm.lib")

struct Last
{
	unsigned long move_time;
	int           volume;
	double        price;
	double        power;
};

const int thread_num = 4;

HANDLE handle[thread_num];
DWORD ThreadIdx[thread_num];
Last last[thread_num][2000];
double *data;
Last *plast = new Last;

DWORD WINAPI AnalysisThread(LPVOID lpParameter)
{
LoopRun:

	CString cs; 
	
	int idx = GetIndex(GetCurrentThreadId());

	cs.Format(_T("线程::::::::%d"), idx);
	PrintString(cs);

	// 分析代码正式开始
	double volume = data[1] - plast->volume < 0 ? data[1] : data[1] - plast->volume;

	double diff_price = data[0] - plast->price;

	double power1 = reverse_operation_a(timeGetTime() - plast->move_time, ladder * step1);

	double power2 = positive_operation_a(diff_price, ladder * step2);

	double power3 = positive_operation_a(volume, ladder * step3);

	double power = sum_all(3, power1, power2, power3);

	bool result = false;

	if ((diff_price > 0 && power > 0) || (diff_price < 0 && power < 0)) result = true;

	SuspendThread(NULL);

	goto LoopRun;

	return power;
}

/***
 *  mqlRates数组索引越大数据越新
***/
int tick(double *tick)
{
	data = tick;

	plast->move_time = timeGetTime();
	plast->price = data[0];
	plast->volume = (int)data[1];

	// 唤醒所有线程
	for (int i = 0; i < thread_num; i++) {
		ResumeThread(handle[i]);
	}

	return 10;
}

void InitAnalysisThread() 
{
	DWORD thread_id = 0;
	for (int i = 0; i < thread_num; i++) {
		handle[i] = CreateThread(0, 0, AnalysisThread, NULL, CREATE_SUSPENDED, &thread_id);
		ThreadIdx[i] = thread_id;
	}
}

int GetIndex(unsigned long thread_id) 
{
	int i;
	for (i = 0; i < thread_num; i++) {
		if (ThreadIdx[i] == thread_id) return i;
	}
	return i;
}