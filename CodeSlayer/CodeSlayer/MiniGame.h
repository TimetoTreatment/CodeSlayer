#pragma once
#include <iostream>
#include<stdio.h>
//
#include <windows.h>
#include <stdio.h>
#include "Console.h"	// cpp ���Ͽ��� �Ű���ϴ�.
#include "Random.h"		// cpp ���Ͽ��� �Ű���ϴ�.
#include "Keyboard.h"	// ������ ���͸� �Է¹������� �־����ϴ�. �Ƹ� ���߿� ���� ���� ���� �� ���ƿ�.

using namespace std;

class MiniGame {
private:
	Console* mConsole;		// ���� ���� -> ��� ������ ����
	Keyboard* mKeyboard;	// Ű���� ��� �߰�
	int _life;
	int _score;
public:
	MiniGame();//�����ڸ� ���� life�� score�� �ʱ�ȭ��Ų��.
	int GetLife();
	int GetScore();
	void SetLife(int L);
	void SetLife();//_life--�� �Ѵ�.
	void SetScore(int S);




	void Main();//- MiniGame Ŭ������ �����Ѵ�.

	bool IsCorrect(char userAnswer, char text, char* Answer);//- ����ڰ� �Է��� ���ڿ��� ���� ���ڿ��� ���Ѵ�.

	void draw_man();//����� �׸���.



	void SetConsoleSize();//�ܼ� ũ�⸦ �����Ѵ�.


};
