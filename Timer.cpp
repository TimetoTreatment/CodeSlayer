#include "Timer.h"

void Timer::Reset()
{
	mStartClock = clock();
}


double Timer::GetElapsedTime()
{
	return ((double)clock() - mStartClock) / CLOCKS_PER_SEC;
}

/*
Timer* Timer::sInstance = nullptr;

Timer* Timer::Instance()
{
	if (sInstance == nullptr)
		sInstance = new Timer;

	return sInstance;
}

void Timer::Release()
{
	delete sInstance;
	sInstance = nullptr;
}
*/