#pragma once
#include <iostream>
#include "Text.h"
#include "Config.h"
#include "Random.h"
#include <fstream>
#include <string>

using namespace std;

class TypingManager {

protected:
	TypingManager() {
		typeSpeed = 0;
		typeaccuracy = 0;
		timetake = 0;
		correct_cnt = 0;
		answer_cnt = 0;
		typenum = 0;
	}
	
	vector<char> Ans;
	vector<Text> Words;
	vector<Text> Shorts;
	vector<Text> Longs;
	/*
	type 1 = word
	type 2 = short
	type 3 = long
	*/
	int typeSpeed;	//Ÿ�� �ӵ�
	double typeaccuracy;	//��Ȯ��
	double timetake;	//�ҿ�ð�
	int correct_cnt;	//���� Ÿ���� ����
	int answer_cnt;		//������ �� Ÿ��
	int typenum;
	char ans;	//���� �Է¹ޱ�
	int pracType;

	//���ϰ���
	Text GetRandomText(int type);
	void readFile();

	//���ϰ� ��ȯ�ϴ� ����� ���ĳ��� �Լ�.
	int TypeSpeed();	//��� Ÿ�ڼӵ�
	double TypeAccuracy();	//��Ȯ��
	double TimeTake(); //�ҿ�ð�

	//setter
	void setAns();	//��� ���� �Է�

	//ä�� ���
	bool IsCorrect();

	//��ü �����
	static TypingManager *sInstance;
	static TypingManager *Instance();
	static void Release();

	//���� ������ ���� ��ü ����
	void InstanceMaker();
};

class WordPractice : TypingManager {
private:
	static WordPractice *sInstance;
public:
	static WordPractice *Instance();
	static void Release();
	WordPractice() {
		typeSpeed = 0;
		typeaccuracy = 100.0;
		timetake = 0;
		correct_cnt = 0;
		answer_cnt = 0;
		typenum = 0;
	}
};

class ShortPractice : TypingManager {
private:
	static ShortPractice *sInstance;
public:
	static ShortPractice *Instance();
	static void Release();
	ShortPractice() {
		typeSpeed = 0;
		typeaccuracy = 100.0;
		timetake = 0;
		correct_cnt = 0;
		answer_cnt = 0;
		typenum = 0;
	}
};

class LongPractice : TypingManager {
private:
	static LongPractice *sInstance;
public:
	static LongPractice *Instance();
	static void Release();
	LongPractice() {
		typeSpeed = 0;
		typeaccuracy = 100.0;
		timetake = 0;
		correct_cnt = 0;
		answer_cnt = 0;
		typenum = 0;
	}
};