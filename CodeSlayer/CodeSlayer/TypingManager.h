#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Text.h"
#include "Config.h"
#include "Random.h"
#include "Timer.h"

using namespace std;

class TypingManager {

private:

	void LoadTextFiles();


protected:

	TypingManager();
	~TypingManager();

	static vector<char>* mAns;
	static vector<Text>* mWords;	// ����ƽ ���� �������Դϴ�.
	static vector<Text>* mShorts;	// ��� �Ļ� Ŭ�������� �ϳ��� ���͸� ����Ű�� ���� �̷��� ��������ϴ�.
	static vector<Text>* mLongs;
	static bool sTextVectorLoaded;
	// ���� Ŭ���� ��� ������ m�� �ٿ��� ǥ���մϴ�. ���� ������ ���� ������ �����մϴ�.
	// �ε��� �� ���� �̷������ �ǹǷ�, üũ ������ ��������ϴ�.

	/*

	type 1 = word
	type 2 = short	// ���� ���, �������� ���� ���ڿ��� ����մϴ�.
	type 3 = long	// GetRandomText(1) ��� GetRandomText("word")�� ���� ����մϴ�.

	*/

	int mRandomIndex;		// GetRandomText �Լ����� ����մϴ�.
	double startTime;		// �� ���׿� ���� ����� �Է��ϱ� ������ �ð��� ��ƵӴϴ�.
	double typeSpeed;		// Ÿ�� �ӵ�
	double typeaccuracy;	// Ÿ�� ��Ȯ��
	double timetake;		// �ҿ�ð�
	int correct_cnt;		// ���� Ÿ���� ����
	int answer_cnt;			// ������ �� Ÿ��
	int typenum;
	char ans;				// ���� �Է¹ޱ�
	int pracType;

	//���ϰ���
	Text GetRandomText(const string& type);	// �������� ���� ���ڿ��� ����մϴ�.
											// ȣ���� ��, ���� ��� "word" ���� ����մϴ�.

	//���ϰ� ��ȯ�ϴ� ����� ���ĳ��� �Լ�.


	//��ü �����

};