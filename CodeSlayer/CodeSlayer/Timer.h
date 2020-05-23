#pragma once
#include <iostream>
#include <time.h>
using namespace std;

class Timer{

	private:
		double start; // 시작시간
		double duration; // 걸린시간
	public:

		void TypingStart(); // 타이핑을 시작했을때 함수
		double TypingEnd(); // 끝냈을 때 함수

};