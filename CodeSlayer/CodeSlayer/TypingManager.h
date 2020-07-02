//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// Ÿ�� ���� ����
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. ����
		- Ÿ�� ���� �Ļ� Ŭ������ ���� ������ �Լ� ����

	2. ���
		- ���� ���� ���� �� ����
		- ������ �ؽ�Ʈ ������ �ҷ��� ��ü�� ����
		- ������ ������ �ؽ�Ʈ ��ȯ
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

	static bool sTextVectorLoaded;	// �ؽ�Ʈ ���� �ε� ����

	static vector<Text>* mWords;	// �ܾ� ������
	static vector<Text>* mShorts;	// ª�� �� ������
	static vector<Text>* mLongs;	// �� �� ������

	void LoadTextFiles();			// ������ �ؽ�Ʈ ���� �ε�

	static vector<Text>* mWordsMeaning;
	static vector<Text>* mShortsMeaning;

	static vector<int>* mRandomTableWord;		// �ܾ� ���� ���̺�
	static vector<int>* mRandomTableShort;		// ª�� �� ���� ���̺�
	static vector<int>* mRandomTableLong;		// �� �� ���� ���̺�
	int mRandomTableIndex;						// ���̺� ���� �ε���

	void SetRandomTable(const string& type);	// ���� ���̺� ����
	int GetRandomTableNum(const string& type);	// ���� ���̺� �� ��ȯ


protected:

	TypingManager();
	~TypingManager();

	Text GetRandomText(const string& type);		// ������ ������ ��ȯ 
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

