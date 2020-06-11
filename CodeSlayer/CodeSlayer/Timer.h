#pragma once
#include <time.h>


class Timer
{
private:
	clock_t mStartClock;

public:
	/* 초기화 */
	void Reset();

	/* 걸린 시간 반환 */
	double GetElapsedTime();
};
