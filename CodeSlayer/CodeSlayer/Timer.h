#pragma once
#include <time.h>


class Timer {

private:
	clock_t mStartClock;		// ���� Ŭ��

public:
	void Reset();				// Ÿ�̸� �ʱ�ȭ
	double GetElapsedTime();	// �ʱ�ȭ�κ��� �ɸ� �ð�(��) ��ȯ

	// ������ ������ �� ���׿�.. �ϴ� ȿ���� �߽��Ͻô� �� ���Ƽ�, ���� ������ �����߽��ϴ�.
	// ��� ����� ������ �����ϴ�.
	// Reset() ���� ���� �ð��� �ʱ�ȭ�ϰ�, �ʿ��� ������ GetElapsedTime() �Լ��� ȣ���մϴ�.


/* �Ʒ��� ���� ���� Ÿ�̸Ӹ� ����� ���� �����Ƿ� ����..

private:
	static Timer* sInstance;

public:
	static Timer* Instance();
	static void Release();
*/
};