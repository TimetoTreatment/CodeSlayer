#include "WordPractice.h"

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

void WordPractice::Main() {
	mTimer = new Timer;
	mConsole = new Console;
	mKeyboard = new Keyboard;
	int testNum = 0;
	string Answer, submit;
	int wrongCnt = 0, correctCnt = 0;
	double time;

	typenum = 0;
	typeSpeed = 0;
	typeaccuracy = 0;

	RenderIntro();
	mConsole->Draw("Assets/layout/wordpractice_main.txt", "white", 0, 1);
	mTimer->Reset();
	for (testNum = 0; testNum < mTestCase; testNum++) {
		AnswerCodes.emplace_back(GetRandomText("word"));
		Answer = AnswerCodes[testNum].GetText();
		mConsole->Draw(Answer, "white", mXAnswerStart, mYAnswerStart);
		mConsole->Color("white");
		mConsole->CursorPosition(mXSubmitStart, mYSubmitStart);
		getline(cin, submit);
		time = mTimer->GetElapsedTime();

		if (submit.length() < Answer.length()) {
			wrongCnt += Answer.length() - submit.length();
			for (int i = 0; i < submit.length(); i++) {
				if (submit[i] != Answer[i]) {
					wrongCnt++;
					typenum++;
				}
				else {
					correctCnt++;
					typenum++;
				}
			}
		}
		else {
			wrongCnt += submit.length() - Answer.length();
			for (int i = 0; i < Answer.length(); i++) {
				if (submit[i] != Answer[i]) {
					wrongCnt++;
					typenum++;
				}
				else {
					correctCnt++;
					typenum++;
				}
			}
		}

		//cout << time;
		typeaccuracy = 100 * (double)correctCnt / (correctCnt + wrongCnt);
		typeSpeed = 60 * (double)typenum / time;

		mConsole->Clear(mXPosSpeed, mYPosSpeed, 4, 1);
		mConsole->Clear(mXPosAccuracy, mYPosAccuracy, 4, 1);
		mConsole->Draw(to_string((int)typeSpeed), "white", mXPosSpeed, mYPosSpeed);
		mConsole->Draw(to_string((int)typeaccuracy), "white", mXPosAccuracy, mYPosAccuracy);

		mConsole->Clear(mXAnswerStart, mYAnswerStart, mWidthCodeBox, mHeightCodeBox);
		mConsole->Clear(mXSubmitStart, mYSubmitStart, mWidthCodeBox, mHeightCodeBox);
	}
	mConsole->Clear(mXPosSpeed, mYPosSpeed, 4, 1);
	mConsole->Clear(mXPosAccuracy, mYPosAccuracy, 4, 1);
	mConsole->Draw(to_string((int)typeSpeed), "white", mXPosSpeed, mYPosSpeed);
	mConsole->Draw(to_string((int)typeaccuracy), "white", mXPosAccuracy, mYPosAccuracy);

	mConsole->Clear();
	mKeyboard->Clear();
}

void WordPractice::RenderIntro()
{
	mConsole->Draw("Assets/layout/wordpractice_intro.txt", "white", 19, 7);
	mConsole->Draw("Typing Practice", "white", 58, 10);
	mConsole->Draw("Word", "yellow", 63, 12);

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
		Sleep(500); // *2
	}
	mConsole->Clear(mXPosPrompt, mYPosPrompt, 25, 1);

	for (int x = 0; x < 3; x++)
		mConsole->Draw("y", "green", mXPosTrafficLight + x * 6, mYPosTrafficLight);

	mConsole->Draw("!! Start !!", "green", mXPosPrompt + 6, mYPosPrompt);
	Sleep(500); // *2
}