#pragma once
#include "TypingManager.h"


class ShortPractice : protected TypingManager
{
private:

	ShortPractice();
	~ShortPractice();

	vector<Text> mPresetCodes;
	queue<int> mRecentAccuracy;
	queue<int> mRecentSpeed;
	int mRecentResultNum;

	const int mTestCase = 10;

	void RenderIntro();
	void RenderPractice();
	void RenderResult();

	void ReadResultFile();
	void WriteResultFile();

public:

	void Main();


private:
	static ShortPractice* sInstance;

public:
	static ShortPractice* Instance();
	static void Release();
};
