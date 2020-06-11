#include "Timer.h"

void Timer::Reset()
{
	mStartClock = clock();
}


double Timer::GetElapsedTime()
{
	return ((double)clock() - mStartClock) / CLOCKS_PER_SEC;
}
