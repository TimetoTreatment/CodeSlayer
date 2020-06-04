#pragma once
#include "TypingManager.h"
#include "Console.h"
#include "Keyboard.h"
#include "Timer.h"
#include <queue>
#include <fstream>

using namespace std;

class LongPractice : public TypingManager
{
private:

	LongPractice();
	~LongPractice();

	Console* mConsole;
	Keyboard* mKeyboard;
	Timer* mTimer;

	vector<Text> mPresetCodes;

	const int mTestCase = 3;

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

	int mTypingSpeed = 0;
	int mTypingAccuracy = 100;
	int mPresetTotalCh = 0;
	int mUserWrongCh = 0;
	int mUserTotalCh = 0;

	void RenderIntro();
	void RenderPractice();
	void RenderResult();
	void WriteResultFIle();

	void OrganizeCode(string& currentline)
	{
		size_t i = 0;

		for (i = 0; i < currentline.size(); i++)
		{
			if (currentline[i] != ' ' && currentline[i] != '\t')
				break;
		}

		currentline.erase(0, i);

		for (i = 0; i < currentline.size(); i++)
		{
			if (currentline[i] == ' ')
			{
				if (i > 0 && IsOperator(currentline[i - 1]))
				{
					currentline.erase(i, 1);
					i--;
				}

				else if (i < currentline.size() - 1 && IsOperator(currentline[i + 1]))
				{
					currentline.erase(i, 1);
					i--;
				}
			}
			else if (currentline[i] == '\t')
			{
				currentline.erase(i, 1);
				i--;
			}
		}
	}

	bool IsOperator(char ch)
	{
		if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=')
			return true;

		if (ch == '&' || ch == '|' || ch == '!' || ch == '>' || ch == '<')
			return true;

		if (ch == '%'  || ch == ',' || ch == ';')
			return true;

		if (ch == '(' || ch == '{' || ch == ')' || ch == '}')
			return true;

		return false;
	}

public:

	void Main();


private:
	static LongPractice* sInstance;

public:
	static LongPractice* Instance();
	static void Release();
};
