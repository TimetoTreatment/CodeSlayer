#pragma once
#include "TypingManager.h"
#include "Timer.h"
#include "Console.h"
#include "Keyboard.h"


class WordPractice : public TypingManager
{
private:
	const int mTestCase = 50;
	const int mXPosPrompt = 53;
	const int mYPosPrompt = 25;
	const int mXPosTrafficLight = 58;
	const int mYPosTrafficLight = 21;

	const int mXAnswerStart = 11;
	const int mYAnswerStart = 17;
	const int mXSubmitStart = 72;
	const int mYSubmitStart = 17;
	const int mXPreviousStart = 72;
	const int mYPreviousStart = 27;

	const int mWidthCodeBox = 50;
	const int mHeightCodeBox = 19;
	const int mHeightInputBox = 1;

	const int mXPosCurrect = 63;
	const int mYPosCurrect = 42;

	const int mXPosAccuracy = 32;
	const int mYPosAccuracy = 7;
	const int mXPosSpeed = 90;
	const int mYPosSpeed = 7;


	Timer* mTimer;
	vector <Text> AnswerCodes;
	Console* mConsole;
	Keyboard* mKeyboard;
public:
	void Main();

private:
	static WordPractice* sInstance;

public:
	static WordPractice* Instance();
	static void Release();
	void RenderIntro();
};

