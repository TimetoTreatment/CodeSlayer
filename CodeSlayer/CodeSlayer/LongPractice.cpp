#include "LongPractice.h"


LongPractice::LongPractice()
{
	mConsole = Console::Instance();
	mKeyboard = Keyboard::Instance();
	mTimer = new Timer;
}


LongPractice::~LongPractice()
{
	delete mTimer;
}


void LongPractice::RenderIntro()
{
	mConsole->Draw("Assets/layout/longpractice_intro.txt", "white", 19, 7);
	mConsole->Draw("Typing Practice", "white", 58, 10);
	mConsole->Draw("Long", "yellow", 63, 12);

	for (;;)
	{
		mConsole->Draw("* Press Enter to Start *", "white", mXPosPrompt, mYPosPrompt);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;

		mConsole->Draw("* Press Enter to Start *", "yellow", mXPosPrompt, mYPosPrompt);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;
	}

	mConsole->Clear(mXPosPrompt, mYPosPrompt, 25, 1);
	mConsole->Draw("0     0     0", "white", mXPosPrompt + 5, mYPosPrompt);

	for (int x = 0; x < 3; x++)
	{
		mConsole->Draw("1", "white", mXPosPrompt + 5 + x * 6, mYPosPrompt);
		mConsole->Draw("y", "red", mXPosTrafficLight + x * 6, mYPosTrafficLight);
		Sleep(200); // *2
	}
	mConsole->Clear(mXPosPrompt, mYPosPrompt, 25, 1);

	for (int x = 0; x < 3; x++)
		mConsole->Draw("y", "green", mXPosTrafficLight + x * 6, mYPosTrafficLight);

	mConsole->Draw("!! Start !!", "green", mXPosPrompt + 6, mYPosPrompt);
	Sleep(200); // *2
}


void LongPractice::RenderPractice()
{
	mConsole->Clear();
	mConsole->Draw("Assets/layout/longpractice_main.txt", "white", 0, 1);

	string persetCode;
	string userLine;
	string userLineOrganized;
	string presetLine;
	size_t prePos, pos;

	int currentLine;

	mTimer->Reset();

	for (int testNum = 0; testNum < mTestCase; testNum++)
	{
		mPresetCodes.emplace_back(GetRandomText("long"));
		persetCode = mPresetCodes[testNum].GetText();

		mConsole->Draw(persetCode, "white", mXPosPresetCodeStart, mYPosPresetCodeStart);

		pos = 0;
		prePos = 0;

		for (currentLine = 0; (pos = persetCode.find('\n', pos + 1)) < persetCode.size(); currentLine++)
		{
			presetLine = persetCode.substr(prePos, pos - prePos);
			prePos = pos + 1;

			OrganizeCode(presetLine);

			mConsole->Color("white");
			mConsole->CursorPosition(mXPosUserCodeStart, mYPosUserCodeStart + currentLine);
			getline(cin, userLine);

			mPresetTotalCh += presetLine.size();
			mUserTotalCh += userLine.size();
			mTypingSpeed = (int)(mUserTotalCh / mTimer->GetElapsedTime() * 60);

			userLineOrganized = userLine;

			OrganizeCode(userLineOrganized);

			if (presetLine == userLineOrganized)
			{
				mConsole->Draw(userLine, "green", mXPosUserCodeStart, mYPosUserCodeStart + currentLine);
				mConsole->Draw("Good", "green", mXPosCurrect, mYPosCurrect);
			}
			else
			{
				for (size_t i = 0; i < presetLine.size(); i++)
				{
					if (i < userLine.size())
					{
						if (userLine[i] != presetLine[i])
							mUserWrongCh++;
					}
					else
						mUserWrongCh++;
				}

				mTypingAccuracy = 100 - mUserWrongCh * 100 / mPresetTotalCh;

				mConsole->Draw(userLine, "red", mXPosUserCodeStart, mYPosUserCodeStart + currentLine);
				mConsole->Draw("Bad ", "red", mXPosCurrect, mYPosCurrect);
			}

			mConsole->Clear(mXPosSpeed, mYPosSpeed, 4, 1);
			mConsole->Clear(mXPosAccuracy, mYPosAccuracy, 4, 1);
			mConsole->Draw(to_string(mTypingSpeed), "white", mXPosSpeed, mYPosSpeed);
			mConsole->Draw(to_string(mTypingAccuracy), "white", mXPosAccuracy, mYPosAccuracy);
		}

		mConsole->Clear(mXPosPresetCodeStart, mYPosPresetCodeStart, mWidthCodeBox, mHeightCodeBox);
		mConsole->Clear(mXPosUserCodeStart, mYPosUserCodeStart, mWidthCodeBox, mHeightCodeBox);
	}
}


void LongPractice::RenderResult()
{
	mConsole->Clear();
	mKeyboard->Clear();

	mConsole->Draw("Assets/layout/longpractice_intro.txt", "white", 19, 7);
	mConsole->Draw("Typing Practice", "white", 58, 10);
	mConsole->Draw("Long", "yellow", 63, 12);

	for (;;)
	{
		mConsole->Draw("* Press Enter to Return *", "white", mXPosPrompt, mYPosPrompt);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;

		mConsole->Draw("* Press Enter to Return *", "yellow", mXPosPrompt, mYPosPrompt);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;
	}

	mConsole->Clear();
	mKeyboard->Clear();
}


void LongPractice::WriteResultFIle()
{
	int count;
	fstream fileAccuracy("Assets/statistics/longaccuracy.txt", ios::in);
	fstream fileSpeed("Assets/statistics/longspeed.txt", ios::in);

	if (fileAccuracy.fail() || fileSpeed.fail())
	{
		cout << "ERROR : LongPractice::WriteResultFIle()\n";
		exit(-1);
	}

	queue<int> recentAccuracy;
	queue<int> recentSpeed;

	string numStr;

	for (count = 0; fileAccuracy >> numStr; count++)
	{
		recentAccuracy.push(stoi(numStr));
		fileSpeed >> numStr;
		recentSpeed.push(stoi(numStr));
	}

	fileAccuracy.close();
	fileSpeed.close();
	fileAccuracy.open("Assets/statistics/longaccuracy.txt", ios::out);
	fileSpeed.open("Assets/statistics/longspeed.txt", ios::out);

	if (fileAccuracy.fail() || fileSpeed.fail())
	{
		cout << "ERROR : LongPractice::WriteResultFIle()\n";
		exit(-1);
	}

	if (count == 5)
	{
		recentAccuracy.pop();
		recentSpeed.pop();
	}

	recentAccuracy.push(mTypingAccuracy);
	recentSpeed.push(mTypingSpeed);

	for (; !recentAccuracy.empty();)
	{
		fileAccuracy << recentAccuracy.front() << ' ';
		fileSpeed << recentSpeed.front() << ' ';

		recentAccuracy.pop();
		recentSpeed.pop();
	}

	fileAccuracy.close();
	fileSpeed.close();
}



void LongPractice::Main()
{
	mConsole->Clear();
	mKeyboard->Clear();

	RenderIntro();
	RenderPractice();
	RenderResult();
	WriteResultFIle();

	mConsole->Clear();
	mKeyboard->Clear();
}


LongPractice* LongPractice::sInstance = nullptr;

LongPractice* LongPractice::Instance() {
	if (sInstance == nullptr) {
		sInstance = new LongPractice;
	}

	return sInstance;
}

void LongPractice::Release() {
	delete sInstance;
	sInstance = nullptr;
}