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

	Console* mConsole;
	Keyboard* mKeyboard;
	Timer* mTimer;

	int mTypingSpeed;
	int mTypingAccuracy;

	Text GetRandomText(const string& type);
};