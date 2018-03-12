

#include "stdafx.h"
#include "analysis.h"
#include <time.h>

#pragma comment(lib, "winmm.lib")

struct DealData
{
	unsigned long move_time = 0;
	int           volume = 0;
	double        price = 0;
};

const int thread_num = 20000;
const int data_len = 2000;

DealData last_deal, cur_deal;

HANDLE handle[thread_num];
DWORD ThreadIdx[thread_num];
double profit[thread_num][data_len]; // 存储每个线程的分析结果
int increased[thread_num]; //每个线程存取数据的位置

DWORD WINAPI AnalysisThread(LPVOID lpParameter)
{
LoopRun:

	int idx = GetIndex(GetCurrentThreadId());

	int diff_volume = cur_deal.volume - last_deal.volume; diff_volume = diff_volume > 0 ? diff_volume : cur_deal.volume;

	double diff_price = cur_deal.price - last_deal.price;

	double power1 = reverse_operation_a(cur_deal.move_time - last_deal.move_time, ladder * step1);

	double power2 = positive_operation_a(diff_price, ladder * step2);

	double power3 = positive_operation_a(diff_volume, ladder * step3);

	double power = sum_all(3, power1, power2, power3);

	if (increased[idx] < data_len) {
		profit[idx][increased[idx]++] = power;
	} else {

	}
		
	SuspendThread(handle[idx]);

	goto LoopRun;

	return power;
}

/***
 *  mqlRates数组索引越大数据越新
***/
int tick(double *data)
{
	if (last_deal.move_time == 0 && last_deal.volume == 0) { // 第一次调用

		last_deal.move_time = timeGetTime();
		last_deal.price = data[0];
		last_deal.volume = (int)data[1];

		cur_deal = last_deal;

		return 0;
	}

	last_deal = cur_deal;

	cur_deal.move_time = timeGetTime();
	cur_deal.price = data[0];
	cur_deal.volume = (int)data[1];

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