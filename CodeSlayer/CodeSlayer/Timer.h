#pragma once
#include <time.h>


class Timer
{
private:
	clock_t mStartClock;

public:
	/* �ʱ�ȭ */
	void Reset();

	/* �ɸ� �ð� ��ȯ */
	double GetElapsedTime();
};
