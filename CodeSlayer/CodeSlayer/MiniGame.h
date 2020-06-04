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
	Random* mRandom;
	Console* mConsole;		// ���� ���� -> ��� ������ ����
	Keyboard* mKeyboard;	// Ű���� ��� �߰�

	int _life;
	int _score;

	int GetLife();
	int GetScore();
	void SetLife(int L);
	void SetLife();//_life--�� �Ѵ�.
	void SetScore(int S);
	void draw_man();//����� �׸���.


public:

	MiniGame();//�����ڸ� ���� life�� score�� �ʱ�ȭ��Ų��.

	/* ���� ���� */
	void Main();//- MiniGame Ŭ������ �����Ѵ�.

	/* ���� �Ǻ� */
	bool IsCorrect(char userAnswer, char text, char* Answer);//- ����ڰ� �Է��� ���ڿ��� ���� ���ڿ��� ���Ѵ�.


private:
	static MiniGame* sInstance;

public:
	static MiniGame* Instance();
	static void Release();
};