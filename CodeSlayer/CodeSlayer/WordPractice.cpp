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


WordPractice::WordPractice()
{

}

WordPractice::~WordPractice()
{

}


void WordPractice::Main() {

	string Answer, submit, previous;

	int wrongCnt = 0;
	int correctCnt = 0;
	int typenum = 0;

	mTypingSpeed = 0;
	mTypingAccuracy = 0;

	RenderIntro();

	mConsole->Draw("Assets/layout/wordpractice_main.txt", "white", 0, 1);
	mTimer->Reset();
	for (int testNum = 0; testNum < mTestCase;) {
		for (int i = 0; i < 10; i++) {
			AnswerCodes.emplace_back(GetRandomText("word"));
			Answer = AnswerCodes[testNum].GetText();
			testNum++;
			mConsole->Draw(Answer, "white", mXAnswerStart, mYAnswerStart + 2 * i);
			mConsole->Color("white");
		}
		testNum -= 10;
		for (int i = 0; i < 10; i++) {
			Answer = AnswerCodes[testNum].GetText();
			mConsole->Draw(Answer, "yellow", mXAnswerStart, mYAnswerStart + 2 * i);
			testNum++;
			mConsole->CursorPosition(mXSubmitStart, mYSubmitStart);
			getline(cin, submit);
			mConsole->Clear(mXPreviousStart, mYPreviousStart, mWidthCodeBox, mHeightInputBox);

			if (submit.length() < Answer.length()) {
				wrongCnt += Answer.length() - submit.length();
				for (size_t i = 0; i < submit.length(); i++) {
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
				for (size_t i = 0; i < Answer.length(); i++) {
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

			mTypingAccuracy = 100 * correctCnt / (correctCnt + wrongCnt);
			mTypingSpeed = (int)(60 * (double) typenum / mTimer->GetElapsedTime());

			previous = submit;
			if (previous == Answer) {
				mConsole->Draw(previous, "green", mXSubmitStart, mYPreviousStart);
				mConsole->Clear(mXPosCurrect, mYPosCurrect, 4, 1);
				mConsole->Draw("Good", "green", mXPosCurrect, mYPosCurrect);
			}
			else {
				mConsole->Draw(previous, "red", mXSubmitStart, mYPreviousStart);
				mConsole->Clear(mXPosCurrect, mYPosCurrect, 4, 1);
				mConsole->Draw("Bad", "red", mXPosCurrect, mYPosCurrect);
			}

			mConsole->Draw(Answer, "white", mXAnswerStart, mYAnswerStart + 2 * i);
			mConsole->Clear(mXPosSpeed, mYPosSpeed, 4, 1);
			mConsole->Clear(mXPosAccuracy, mYPosAccuracy, 4, 1);
			mConsole->Draw(to_string((int)mTypingSpeed), "white", mXPosSpeed, mYPosSpeed);
			mConsole->Draw(to_string((int)mTypingAccuracy), "white", mXPosAccuracy, mYPosAccuracy);
			mConsole->Clear(mXSubmitStart, mYSubmitStart, mWidthCodeBox, mHeightInputBox);

			mConsole->Clear(mXPosSpeed, mYPosSpeed, 4, 1);
			mConsole->Clear(mXPosAccuracy, mYPosAccuracy, 4, 1);
			mConsole->Draw(to_string((int)mTypingSpeed), "white", mXPosSpeed, mYPosSpeed);
			mConsole->Draw(to_string((int)mTypingAccuracy), "white", mXPosAccuracy, mYPosAccuracy);
		}
		mConsole->Clear(mXAnswerStart, mYAnswerStart, mWidthCodeBox, mHeightCodeBox);
	}

	RenderResult();

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

	mConsole->Clear();
}

void WordPractice::RenderResult()
{
	mConsole->Clear();
	mKeyboard->Clear();

	mConsole->Draw("Assets/layout/longpractice_intro.txt", "white", 19, 7);
	mConsole->Draw("Speed : ", "white", mXPosTitleStart + 3, mYPosTitleStart);
	mConsole->CursorPosition(mXPosTitleStart + 11, mYPosTitleStart);

	cout << mTypingSpeed;
	mConsole->Color("white");
	cout << " / min";

	mConsole->Draw("Accuracy : ", "white", mXPosTitleStart, mYPosTitleStart + 2);
	mConsole->CursorPosition(mXPosTitleStart + 11, mYPosTitleStart + 2);

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