//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 타자 연습 공통
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. 개요
		- 타자 연습 파생 클래스의 공용 변수와 함수 정의

	2. 기능
		- 공용 변수 선언 및 정의
		- 프리셋 텍스트 파일을 불러와 객체에 저장
		- 무작위 프리셋 텍스트 반환
*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "Text.h"
#include "Config.h"
#include "Random.h"
#include "Timer.h"
#include "Console.h"
#include "Keyboard.h"
#include "UserAnalysis.h"

using namespace std;


class TypingManager
{
private:

	static bool sTextVectorLoaded;	// 텍스트 벡터 로드 여부

	static vector<Text>* mWords;	// 단어 프리셋
	static vector<Text>* mShorts;	// 짧은 글 프리셋
	static vector<Text>* mLongs;	// 긴 글 프리셋

	void LoadTextFiles();			// 프리셋 텍스트 파일 로드

	static vector<Text>* mWordsMeaning;
	static vector<Text>* mShortsMeaning;

	static vector<int>* mRandomTableWord;		// 단어 난수 테이블
	static vector<int>* mRandomTableShort;		// 짧은 글 난수 테이블
	static vector<int>* mRandomTableLong;		// 긴 글 난수 테이블
	int mRandomTableIndex;						// 테이블 선택 인덱스

	void SetRandomTable(const string& type);	// 난수 테이블 생성
	int GetRandomTableNum(const string& type);	// 난수 테이블 값 반환


protected:

	TypingManager();
	~TypingManager();

	Text GetRandomText(const string& type);		// 무작위 프리셋 반환 
	Text GetRandomTextMeaning(const string& type)
	{
		if (type == "word")
			return mWordsMeaning->at(mRandomTableWord->at(mRandomTableIndex));

		else if (type == "short")
			return mShortsMeaning->at(mRandomTableShort->at(mRandomTableIndex));

		else
		{
			cout << "Error : TypingManager::GetRandomTextMeaning" << endl;
			exit(-1);
		}
	}

	int GetRandomTableIndex(const string& type)
	{
		if (type == "word")
			return mRandomTableWord->at(mRandomTableIndex);

		else
			return mRandomTableShort->at(mRandomTableIndex);
	}

	Console* mConsole;
	Keyboard* mKeyboard;
	Timer* mTimer;
	UserAnalysis* mUserAnalysis;

	int mTypingSpeed;
	int mTypingAccuracy;

	const int mXPosTitleStart = 56;
	const int mYPosTitleStart = 10;

	const int mXPosPrompt = 53;
	const int mYPosPrompt = 25;
	const int mXPosTrafficLight = 58;
	const int mYPosTrafficLight = 21;

	const int mXPosPresetCodeStart = 11;
	const int mYPosPresetCodeStart = 17;
	const int mXPosUserCodeStart = 72;
	const int mYPosUserCodeStart = 17;

	const int mWidthCodeBox = 52;
	const int mHeightCodeBox = 24;

	const int mXPosCurrect = 63;
	const int mYPosCurrect = 42;

	const int mXPosAccuracy = 32;
	const int mYPosAccuracy = 7;
	const int mXPosSpeed = 90;
	const int mYPosSpeed = 7;

	int mPresetTotalCh = 0;
	int mUserWrongCh = 0;
	int mUserTotalCh = 0;
};

