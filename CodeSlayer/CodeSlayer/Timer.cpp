#include "Timer.h"

void Timer::Reset()
{
	mStartClock = clock();		// 시작 시각을 현재 시각으로 초기화
}


double Timer::GetElapsedTime()
{
	return ((double)clock() - mStartClock) / CLOCKS_PER_SEC;	// 걸린 시간을 초 단위로 반환
}
