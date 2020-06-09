#pragma once
#include "Random.h"
#include "Console.h"
#include "Config.h"
#include "Keyboard.h"
#include <iostream>
#include <unordered_map>

using namespace std;


class MiniGame
{
private:

	Console* mConsole;
	Keyboard* mKeyboard;
	Random* mRandom;

	const int mStartLife = 8;
	int mLife = 0;

	unordered_map<int, string> mLifeToGrade = {
		{8, "A+"},
		{7, "A0"},
		{6, "B+"},
		{5, "B0"},
		{4, "C+"},
		{3, "C0"},
		{2, "D+"},
		{1, "D0"},
		{0, "F"},
	};

	bool mQuit = false;

	const int mXPosCin = 29;
	const int mYPosCin = 41;
	const int mWidthCinBox = 11;
	const int mHeightCinBox = 1;

	const int mXPosCout = 91;
	const int mYPosCout = 41;
	const int mWidthCoutBox = 11;
	const int mHeightCoutBox = 1;

	const int mXPosCorrect = 63;
	const int mYPosCorrect = 41;

	const int mXPosPresetCodeStart = 11;
	const int mYPosPresetCodeStart = 17;
	const int mXPosUserCodeStart = 72;
	const int mYPosUserCodeStart = 17;

	const int mXPosUserScript = 78;
	const int mYPosUserScript = 20;

	const int mWidthCodeBox = 51;
	const int mHeightCodeBox = 23;

	const int mXPosGallows = 85;
	const int mYPosGallows = 25;

	const int mXPosTitleStart = 54;
	const int mYPosTitleStart = 10;

	const int mXPosPrompt = 53;
	const int mYPosPrompt = 23;
	const int mXPosTrafficLight = 58;
	const int mYPosTrafficLight = 19;

	const int mXPosEnding = 50;
	const int mYPosEnding = 30;

	MiniGame();



	void RenderIntro();
	void RenderGame();
	void RenderResult();

	void DrawHangman(bool isEnding);
	bool IsCorrect(char userAnswer, char text, char* Answer);

public:

	void Main();


private:
	static MiniGame* sInstance;

public:
	static MiniGame* Instance();
	static void Release();
};