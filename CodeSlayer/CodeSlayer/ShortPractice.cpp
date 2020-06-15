#include "ShortPractice.h"


ShortPractice::ShortPractice()
{
	mRecentResultNum = 0;
}


ShortPractice::~ShortPractice()
{

}


void ShortPractice::RenderIntro()
{
	mConsole->Draw("Assets/layout/practice_intro.txt", "white", 19, 7);
	mConsole->Draw("Typing Practice", "white", mXPosTitleStart + 2, mYPosTitleStart);
	mConsole->Draw("Short", "green", mXPosTitleStart + 7, mYPosTitleStart + 2);

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
		Sleep(1000); // 1000
	}
	mConsole->Clear(mXPosPrompt, mYPosPrompt, 25, 1);

	for (int x = 0; x < 3; x++)
		mConsole->Draw("y", "green", mXPosTrafficLight + x * 6, mYPosTrafficLight);

	mConsole->Draw("!! Start !!", "green", mXPosPrompt + 6, mYPosPrompt);
	Sleep(1000); // 1000
}


void ShortPractice::RenderPractice()
{
	string presetCode;
	string userCode;
	int currentWord;
	int testPageNum = (mTestCase - 1) / 5 + 1;

	mKeyboard->Clear();
	mConsole->Clear();
	mConsole->Draw("Assets/layout/practice_main.txt", "white", 0, 1);
	mTimer->Reset();

	mPresetTotalCh = 0;
	mUserWrongCh = 0;
	mUserTotalCh = 0;

	for (int testPageCount = 0; testPageCount < testPageNum; testPageCount++)
	{
		mPresetCodes.clear();

		for (currentWord = 0; currentWord < 5 && testPageCount * 5 + currentWord < mTestCase; currentWord++)
		{
			mPresetCodes.emplace_back(GetRandomText("short"));
			presetCode = mPresetCodes[currentWord].GetText();

			mConsole->Draw(presetCode, "yellow", mXPosPresetCodeStart, mYPosPresetCodeStart + currentWord * 3);

			mConsole->Color("white");
			mConsole->CursorPosition(mXPosUserCodeStart, mYPosUserCodeStart + currentWord * 3);

			getline(cin, userCode);

			mPresetTotalCh += presetCode.size();
			mUserTotalCh += userCode.size();
			mTypingSpeed = (int)(mUserTotalCh / mTimer->GetElapsedTime() * 60);

			if (presetCode == userCode)
			{
				mConsole->Draw(userCode, "green", mXPosUserCodeStart, mYPosUserCodeStart + currentWord * 3);
				mConsole->Draw("Good", "green", mXPosCurrect, mYPosCurrect);
			}
			else
			{
				for (size_t count = 0; count < presetCode.size(); count++)
				{
					if (count < userCode.size())
					{
						if (userCode[count] != presetCode[count])
							mUserWrongCh++;
					}
					else
						mUserWrongCh++;
				}

				mTypingAccuracy = 100 - mUserWrongCh * 100 / mPresetTotalCh;

				mConsole->Draw(userCode, "red", mXPosUserCodeStart, mYPosUserCodeStart + currentWord * 3);
				mConsole->Draw("Bad ", "red", mXPosCurrect, mYPosCurrect);
			}

			mConsole->Draw(presetCode, "white", mXPosPresetCodeStart, mYPosPresetCodeStart + currentWord * 3);
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


void ShortPractice::RenderResult()
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


void ShortPractice::ReadResultFile()
{
	string numStr;
	fstream fileAccuracy("Assets/statistics/shortaccuracy.txt", ios::in);
	fstream fileSpeed("Assets/statistics/shortspeed.txt", ios::in);

	if (fileAccuracy.fail() || fileSpeed.fail())
	{
		cout << "ERROR : ShortPractice::WriteResultFIle()\n";
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


void ShortPractice::WriteResultFile()
{
	fstream fileAccuracy("Assets/statistics/shortaccuracy.txt", ios::out);
	fstream fileSpeed("Assets/statistics/shortspeed.txt", ios::out);

	if (fileAccuracy.fail() || fileSpeed.fail())
	{
		cout << "ERROR : ShortPractice::WriteResultFIle()\n";
		exit(-1);
	}

	if (mRecentResultNum == 5)
	{
		mRecentAccuracy.pop();
		mRecentSpeed.pop();
	}

	mRecentAccuracy.push(mTypingAccuracy);
	mRecentSpeed.push(mTypingSpeed);

	for (; mRecentAccuracy.size() > 1;)
	{
		fileAccuracy << mRecentAccuracy.front() << ' ';
		fileSpeed << mRecentSpeed.front() << ' ';

		mRecentAccuracy.pop();
		mRecentSpeed.pop();
	}

	fileAccuracy << mRecentAccuracy.front();
	fileSpeed << mRecentSpeed.front();

	mRecentAccuracy.pop();
	mRecentSpeed.pop();
}


void ShortPractice::Main()
{
	ReadResultFile();
	RenderIntro();
	RenderPractice();
	RenderResult();
	WriteResultFile();

	mPresetCodes.clear();
}


ShortPractice* ShortPractice::sInstance = nullptr;

ShortPractice* ShortPractice::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ShortPractice;
	}

	return sInstance;
}

void ShortPractice::Release() {
	delete sInstance;
	sInstance = nullptr;
}