#pragma once
#include <time.h>


class Timer {

private:
	clock_t mStartClock;		// 기준 클럭

public:
	void Reset();				// 타이머 초기화
	double GetElapsedTime();	// 초기화로부터 걸린 시간(초) 반환

	// 수정한 사항이 좀 많네요.. 일단 효율을 중시하시는 것 같아서, 많은 변수를 삭제했습니다.
	// 사용 방법은 이전과 같습니다.
	// Reset() 으로 시작 시간을 초기화하고, 필요한 곳에서 GetElapsedTime() 함수를 호출합니다.


/* 아래는 여러 개의 타이머를 사용할 수도 있으므로 생략..

private:
	static Timer* sInstance;

public:
	static Timer* Instance();
	static void Release();
*/
};