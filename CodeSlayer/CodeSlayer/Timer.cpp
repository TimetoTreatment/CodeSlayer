#include "Timer.h"

void Timer::Reset()
{
	mStartClock = clock();		// ���� �ð��� ���� �ð����� �ʱ�ȭ
}


double Timer::GetElapsedTime()
{
	return ((double)clock() - mStartClock) / CLOCKS_PER_SEC;	// �ɸ� �ð��� �� ������ ��ȯ
}
