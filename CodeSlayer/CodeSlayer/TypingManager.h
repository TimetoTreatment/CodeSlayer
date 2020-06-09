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

using namespace std;

class TypingManager {

private:

	static vector<Text>* mWords;
	static vector<Text>* mShorts;
	static vector<Text>* mLongs;
	static bool sTextVectorLoaded;

	void LoadTextFiles();

	static vector<int>* mRandomTableWord;
	static vector<int>* mRandomTableShort;
	static vector<int>* mRandomTableLong;
	int mRandomTableIndex;

	void SetRandomTable(const string& type);
	int GetRandomTableNum(const string& type);

protected:

	TypingManager();
	~TypingManager();

	Text GetRandomText(const string& type);

	Console* mConsole;
	Keyboard* mKeyboard;
	Timer* mTimer;

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

	const int mWidthCodeBox = 50;
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