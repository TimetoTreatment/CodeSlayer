#pragma once
#include "TypingManager.h"

using namespace std;

class ShortPractice : public TypingManager
{
private:

	ShortPractice();
	~ShortPractice();

	vector<Text> mPresetCodes;
	queue<int> mRecentAccuracy;
	queue<int> mRecentSpeed;
	int mRecentResultNum;

	const int mTestCase = 25;

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
