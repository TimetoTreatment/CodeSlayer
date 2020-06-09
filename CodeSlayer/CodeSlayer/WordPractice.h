#pragma once
#include "TypingManager.h"


class WordPractice : protected TypingManager
{
private:

	WordPractice();
	~WordPractice();

	vector<Text> mPresetCodes;
	queue<int> mRecentAccuracy;
	queue<int> mRecentSpeed;
	int mRecentResultNum;

	const int mTestCase = 50;

	void RenderIntro();
	void RenderPractice();
	void RenderResult();

	void ReadResultFile();
	void WriteResultFile();

public:

	void Main();


private:
	static WordPractice* sInstance;

public:
	static WordPractice* Instance();
	static void Release();
};
