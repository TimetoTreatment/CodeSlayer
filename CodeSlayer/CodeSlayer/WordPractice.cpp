#include "WordPractice.h"


WordPractice::WordPractice()
{
	mRecentResultNum = 0;
}


WordPractice::~WordPractice()
{

}


void WordPractice::RenderIntro()
{
	mConsole->Draw("Assets/layout/practice_intro.txt", "white", 19, 7);
	mConsole->Draw("Typing Practice", "white", mXPosTitleStart + 2, mYPosTitleStart);
	mConsole->Draw("Word", "red", mXPosTitleStart + 7, mYPosTitleStart + 2);

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
		Sleep(200); // *5
	}
	mConsole->Clear(mXPosPrompt, mYPosPrompt, 25, 1);

	for (int x = 0; x < 3; x++)
		mConsole->Draw("y", "green", mXPosTrafficLight + x * 6, mYPosTrafficLight);

	mConsole->Draw("!! Start !!", "green", mXPosPrompt + 6, mYPosPrompt);
	Sleep(200); // *5
}


void WordPractice::RenderPractice()
{
	string presetCode;
	string userLine;
	string presetLine;
	int currentWord;
	int testPageNum = (mTestCase - 1) / 10 + 1;

	mKeyboard->Clear();
	mConsole->Clear();
	mConsole->Draw("Assets/layout/practice_main.txt", "white", 0, 1);
	mTimer->Reset();

	for (int testPageCount = 0; testPageCount < testPageNum; testPageCount++)
	{
		mPresetCodes.clear();

		for (currentWord = 0; currentWord < 10 && testPageCount * 10 + currentWord < mTestCase; currentWord++)
		{
			mPresetCodes.emplace_back(GetRandomText("word"));
			presetCode = mPresetCodes[currentWord].GetText();

			mConsole->Draw(presetCode, "yellow", mXPosPresetCodeStart, mYPosPresetCodeStart + currentWord * 2);

			mConsole->Color("white");
			mConsole->CursorPosition(mXPosUserCodeStart, mYPosUserCodeStart + currentWord * 2);

			getline(cin, userLine);

			mPresetTotalCh += presetCode.size();
			mUserTotalCh += userLine.size();
			mTypingSpeed = (int)(mUserTotalCh / mTimer->GetElapsedTime() * 60);

			if (presetCode == userLine)
			{
				mConsole->Draw(userLine, "green", mXPosUserCodeStart, mYPosUserCodeStart + currentWord * 2);
				mConsole->Draw("Good", "green", mXPosCurrect, mYPosCurrect);
			}
			else
			{
				for (size_t count = 0; count < presetCode.size(); count++)
				{
					if (count < userLine.size())
					{
						if (userLine[count] != presetCode[count])
							mUserWrongCh++;
					}
					else
						mUserWrongCh++;
				}

				mTypingAccuracy = 100 - mUserWrongCh * 100 / mPresetTotalCh;

				mConsole->Draw(userLine, "red", mXPosUserCodeStart, mYPosUserCodeStart + currentWord * 2);
				mConsole->Draw("Bad ", "red", mXPosCurrect, mYPosCurrect);
			}

			mConsole->Draw(presetLine, "white", mXPosPresetCodeStart, mYPosPresetCodeStart + currentWord * 2);
			mConsole->Clear(mXPosSpeed, mYPosSpeed, 4, 1);
			mConsole->Clear(mXPosAccuracy, mYPosAccuracy, 4, 1);
			mConsole->Draw(to_string(mTypingSpeed), "white", mXPosSpeed, mYPosSpeed);
			mConsole->Draw(to_string(mTypingAccuracy), "white", mXPosAccuracy, mYPosAccuracy);
		}

		mConsole->Clear(mXPosPresetCodeStart, mYPosPresetCodeStart, mWidthCodeBox, mHeightCodeBox);
		mConsole->Clear(mXPosUserCodeStart, mYPosUserCodeStart, mWidthCodeBox, mHeightCodeBox);
	}

	mConsole->Clear();
	mKeyboard->Clear();
}


void WordPractice::RenderResult()
{
	mConsole->Clear();
	mKeyboard->Clear();

	mConsole->Draw("Assets/layout/practice_intro.txt", "white", 19, 7);
	mConsole->Draw("Speed : ", "white", mXPosTitleStart + 3, mYPosTitleStart);
	mConsole->CursorPosition(mXPosTitleStart + 11, mYPosTitleStart);

	if (mTypingSpeed >= mRecentSpeed.back())
		mConsole->Color("green");
	else mConsole->Color("red");

	cout << mTypingSpeed;
	mConsole->Color("white");
	cout << " / min";

	mConsole->Draw("Accuracy : ", "white", mXPosTitleStart, mYPosTitleStart + 2);
	mConsole->CursorPosition(mXPosTitleStart + 11, mYPosTitleStart + 2);

	if (mTypingAccuracy >= mRecentAccuracy.back())
		mConsole->Color("green");
	else mConsole->Color("red");

	cout << mTypingAccuracy;
	mConsole->Color("white");
	cout << " %";

	for (;;)
	{
		mConsole->Draw("* Press Enter to Quit *", "white", mXPosPrompt, mYPosPrompt);
		mConsole->Draw("y", "random", mXPosTrafficLight, mYPosTrafficLight);
		mConsole->Draw("y", "random", mXPosTrafficLight + 6, mYPosTrafficLight);
		mConsole->Draw("y", "random", mXPosTrafficLight + 12, mYPosTrafficLight);
		mConsole->CursorPosition(0, 0);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;

		mConsole->Draw("* Press Enter to Quit *", "yellow", mXPosPrompt, mYPosPrompt);
		mConsole->Draw("y", "random", mXPosTrafficLight, mYPosTrafficLight);
		mConsole->Draw("y", "random", mXPosTrafficLight + 6, mYPosTrafficLight);
		mConsole->Draw("y", "random", mXPosTrafficLight + 12, mYPosTrafficLight);
		mConsole->CursorPosition(0, 0);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;
	}

	mConsole->Clear();
	mKeyboard->Clear();
}


void WordPractice::ReadResultFile()
{
	string numStr;
	fstream fileAccuracy("Assets/statistics/longaccuracy.txt", ios::in);
	fstream fileSpeed("Assets/statistics/longspeed.txt", ios::in);

	if (fileAccuracy.fail() || fileSpeed.fail())
	{
		cout << "ERROR : WordPractice::WriteResultFIle()\n";
		exit(-1);
	}

	for (mRecentResultNum = 0; fileAccuracy >> numStr; mRecentResultNum++)
	{
		mRecentAccuracy.push(stoi(numStr));
		fileSpeed >> numStr;
		mRecentSpeed.push(stoi(numStr));
	}

	fileAccuracy.close();
	fileSpeed.close();
}


void WordPractice::WriteResultFile()
{
	fstream fileAccuracy("Assets/statistics/longaccuracy.txt", ios::out);
	fstream fileSpeed("Assets/statistics/longspeed.txt", ios::out);

	if (fileAccuracy.fail() || fileSpeed.fail())
	{
		cout << "ERROR : WordPractice::WriteResultFIle()\n";
		exit(-1);
	}

	if (mRecentResultNum == 5)
	{
		mRecentAccuracy.pop();
		mRecentSpeed.pop();
	}

	mRecentAccuracy.push(mTypingAccuracy);
	mRecentSpeed.push(mTypingSpeed);

	for (; !mRecentAccuracy.empty();)
	{
		fileAccuracy << mRecentAccuracy.front() << ' ';
		fileSpeed << mRecentSpeed.front() << ' ';

		mRecentAccuracy.pop();
		mRecentSpeed.pop();
	}

	fileAccuracy.close();
	fileSpeed.close();
}


void WordPractice::Main()
{
	ReadResultFile();
	RenderIntro();
	RenderPractice();
	RenderResult();
	WriteResultFile();

	mPresetCodes.clear();
}


WordPractice* WordPractice::sInstance = nullptr;

WordPractice* WordPractice::Instance() {
	if (sInstance == nullptr) {
		sInstance = new WordPractice;
	}

	return sInstance;
}

void WordPractice::Release() {
	delete sInstance;
	sInstance = nullptr;
}