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