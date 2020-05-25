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
	int typeSpeed;	//타자 속도
	double typeaccuracy;	//정확도
	double timetake;	//소요시간
	int correct_cnt;	//맞은 타수의 갯수
	int answer_cnt;		//정답의 총 타수
	int typenum;
	char ans;	//문자 입력받기
	int pracType;

	//파일관련
	Text GetRandomText(int type);
	void readFile();

	//구하고 반환하는 기능을 합쳐놓은 함수.
	int TypeSpeed();	//평균 타자속도
	double TypeAccuracy();	//정확도
	double TimeTake(); //소요시간

	//setter
	void setAns();	//답안 문자 입력

	//채점 기능
	bool IsCorrect();

	//객체 만들기
	static TypingManager *sInstance;
	static TypingManager *Instance();
	static void Release();

	//연습 유형에 따른 객체 생성
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