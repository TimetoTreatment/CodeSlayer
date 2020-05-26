#pragma once
#include <iostream>
#include<stdio.h>
//
#include <windows.h>
#include <stdio.h>
using namespace std;

class MiniGame {
private:
	int _life;
	int _score;
public:
	MiniGame();//생성자를 통해 life와 score를 초기화시킨다.
	int _GetLife();
	int _GetScore();
	void _SetLife(int L);
	void _SetLife();//_life--을 한다.
	void _SetScore(int S);




	void Main();//- MiniGame 클래스를 실행한다.

	bool IsCorrect(char userAnswer, char text, char* Answer);//- 사용자가 입력한 문자열과 정답 문자열을 비교한다.

	void draw_man();//행맨을 그린다.



	void SetConsoleSize();//콘솔 크기를 세팅한다.


};
