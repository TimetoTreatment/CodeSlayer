#pragma once
#include <iostream>
#include <time.h>
using namespace std;

class Timer{

	private:
		double start; // ���۽ð�
		double duration; // �ɸ��ð�
	public:

		void TypingStart(); // Ÿ������ ���������� �Լ�
		double TypingEnd(); // ������ �� �Լ�

};