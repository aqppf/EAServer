

#include "stdafx.h"
#include "analysis.h"
#include <time.h>

#pragma comment(lib, "winmm.lib")

/***
 *  基本公式 diff_price * diff_time * diff_volume
***/

struct DealData
{
	unsigned long move_time = 0;
	int           volume = 0;
	double        price = 0;
};

struct Modulus
{
	double ratio1;
	double ratio2;
};

struct Profit
{
	double power;
	double price;
	double average; //长度为num的平均值
	int num;
};

const int thread_num = 2000;
const int data_len = 1000;

DealData last_deal, cur_deal;

HANDLE handle[thread_num];
DWORD ThreadIdx[thread_num];

Modulus modulus[thread_num];

Profit profit[thread_num][data_len]; // 存储每个线程的分析结果
int increased[thread_num]; //每个线程存取数据的位置

DWORD WINAPI AnalysisThread(LPVOID lpParameter)
{
LoopRun:

	int earliest, idx, diff_volume;
	double total = 0 , diff_price, time, volume, power;

	idx = GetIndex(GetCurrentThreadId());

	diff_volume = cur_deal.volume - last_deal.volume; diff_volume = diff_volume > 0 ? diff_volume : cur_deal.volume;

	diff_price = cur_deal.price - last_deal.price;

	time = reverse_operation_a(cur_deal.move_time - last_deal.move_time, modulus[idx].ratio1);

	volume = positive_operation_a(diff_volume, modulus[idx].ratio2);

	power = multiply_all(3, diff_price, time, volume);

	if (increased[idx] < data_len) {
		profit[idx][increased[idx]++].price = cur_deal.price;
		profit[idx][increased[idx]++].power = power;
		goto Suspend;
	}

	earliest = increased[idx]++ - data_len;

	if (increased[idx] >= 2 * data_len) increased[idx] -= data_len;

	profit[idx][earliest].power = power;
	profit[idx][earliest].price = cur_deal.price;

	//计算平均值
	for (size_t i = 0; i < data_len; i++)
	{
		total += profit[idx][i].power;
	}

	profit[idx][earliest].average = total / data_len;

Suspend:
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
	CString cs;

	DWORD thread_id = 0;
	for (int i = 0; i < thread_num; i++) {
		handle[i] = CreateThread(0, 0, AnalysisThread, NULL, CREATE_SUSPENDED, &thread_id);
		ThreadIdx[i] = thread_id;

		//初始化每个线程的计算系数
		modulus[i].ratio1 = GetStep1() * GetLadder();
		modulus[i].ratio2 = GetStep1() * GetLadder();

		cs.Format(_T("init id::%d, step1::%.20f, step2::%.20f"), i, 
			modulus[i].ratio1, 
			modulus[i].ratio2);

		PrintString(cs);
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