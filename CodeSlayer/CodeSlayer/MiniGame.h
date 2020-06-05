#pragma once
#include <iostream>
#include<stdio.h>
//
#include <windows.h>
#include <stdio.h>
#include "Console.h"	// cpp 파일에서 옮겼습니다.
#include "Random.h"		// cpp 파일에서 옮겼습니다.
#include "Keyboard.h"	// 마지막 엔터를 입력받으려고 넣었습니다. 아마 나중에 쓰실 일이 있을 것 같아요.

using namespace std;

class MiniGame {
private:
	Random* mRandom;
	Console* mConsole;		// 지역 변수 -> 멤버 변수로 변경
	Keyboard* mKeyboard;	// 키보드 멤버 추가

	int _life;
	int _score;

	int GetLife();

	void SetLife(int L);
	void SetLife();//_life--을 한다.

	void draw_man();//행맨을 그린다.


public:

	MiniGame();//생성자를 통해 life와 score를 초기화시킨다.

	/* 메인 루프 */
	void Main();//- MiniGame 클래스를 실행한다.

	/* 정답 판별 */
	bool IsCorrect(char userAnswer, char text, char* Answer);//- 사용자가 입력한 문자열과 정답 문자열을 비교한다.


private:
	static MiniGame* sInstance;

public:
	static MiniGame* Instance();
	static void Release();
};
