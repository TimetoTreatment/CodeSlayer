#include "LongPractice.h"


LongPractice::LongPractice()
{

}


LongPractice::~LongPractice()
{

}


void LongPractice::RenderIntro()
{
	mConsole->Draw("Assets/layout/practice_intro.txt", "white", 19, 7);
	mConsole->Draw("Typing Practice", "white", mXPosTitleStart + 2, mYPosTitleStart);
	mConsole->Draw("Long", "yellow", mXPosTitleStart + 7, mYPosTitleStart + 2);

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


void LongPractice::RenderPractice()
{
	string presetCode;
	string userLine;
	string userLineOrganized;
	string presetLine;
	string presetLineOrganized;
	size_t prePos, pos;
	size_t currentLine;
	size_t indentation;
	size_t CurrentIndentation;

	mKeyboard->Clear();
	mConsole->Clear();
	mConsole->Draw("Assets/layout/practice_main.txt", "white", 0, 1);
	mTimer->Reset();

	mPresetTotalCh = 0;
	mUserWrongCh = 0;
	mUserTotalCh = 0;

	for (int testNum = 0; testNum < mTestCase; testNum++)
	{
		mPresetCodes.emplace_back(GetRandomText("long"));
		presetCode = mPresetCodes[testNum].GetText();

		mConsole->Draw(presetCode, "white", mXPosPresetCodeStart, mYPosPresetCodeStart);

		pos = 0;
		prePos = 0;

		for (currentLine = 0; (pos = presetCode.find('\n', pos + 1)) < presetCode.size(); currentLine++)
		{
			presetLine = presetCode.substr(prePos, pos - prePos);
			mConsole->Draw(presetLine, "yellow", mXPosPresetCodeStart, mYPosPresetCodeStart + currentLine);
			prePos = pos + 1;

			indentation = Whitespace(presetLine);
			presetLineOrganized = presetLine;
			OrganizeCode(presetLineOrganized);

			mConsole->Color("white");
			mConsole->CursorPosition(mXPosUserCodeStart, mYPosUserCodeStart + currentLine);

			for (CurrentIndentation = 0; CurrentIndentation < indentation; CurrentIndentation++)
				cout << " ";

			getline(cin, userLine);

			userLineOrganized = userLine;
			OrganizeCode(userLineOrganized);

			mPresetTotalCh += presetLineOrganized.size();
			mUserTotalCh += userLineOrganized.size();
			mTypingSpeed = (int)(mUserTotalCh / mTimer->GetElapsedTime() * 60);

			if (presetLineOrganized == userLineOrganized)
			{
				mConsole->Draw(userLine, "green", mXPosUserCodeStart + indentation, mYPosUserCodeStart + currentLine);
				mConsole->Draw("Good", "green", mXPosCurrect, mYPosCurrect);
			}
			else
			{
				for (size_t count = 0; count < presetLineOrganized.size(); count++)
				{
					if (count < userLine.size())
					{
						if (userLine[count] != presetLineOrganized[count])
							mUserWrongCh++;
					}
					else
						mUserWrongCh++;
				}

				mConsole->Draw(userLine, "red", mXPosUserCodeStart + indentation, mYPosUserCodeStart + currentLine);
				mConsole->Draw("Bad ", "red", mXPosCurrect, mYPosCurrect);
			}

			mTypingAccuracy = 100 - mUserWrongCh * 100 / mPresetTotalCh;

			mConsole->Draw(presetLine, "white", mXPosPresetCodeStart, mYPosPresetCodeStart + currentLine);
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


void LongPractice::RenderResult()
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


void LongPractice::ReadResultFile()
{
	string numStr;
	fstream fileAccuracy("Assets/statistics/longaccuracy.txt", ios::in);
	fstream fileSpeed("Assets/statistics/longspeed.txt", ios::in);

	if (fileAccuracy.fail() || fileSpeed.fail())
	{
		cout << "ERROR : LongPractice::WriteResultFIle()\n";
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


void LongPractice::WriteResultFile()
{
	fstream fileAccuracy("Assets/statistics/longaccuracy.txt", ios::out);
	fstream fileSpeed("Assets/statistics/longspeed.txt", ios::out);

	if (fileAccuracy.fail() || fileSpeed.fail())
	{
		cout << "ERROR : LongPractice::WriteResultFIle()\n";
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

	fileAccuracy.close();
	fileSpeed.close();
}


size_t LongPractice::Whitespace(const string& currentLine) const
{
	size_t indentation;

	for (indentation = 0; indentation < currentLine.size(); indentation++)
	{
		if (currentLine[indentation] != ' ' && currentLine[indentation] != '\t')
			break;
	}

	return indentation;
}


void LongPractice::OrganizeCode(string& currentLine)
{
	size_t i;

	for (i = 0; i < currentLine.size(); i++)
	{
		if (currentLine[i] != ' ' && currentLine[i] != '\t')
			break;
	}

	currentLine.erase(0, i);

	for (i = 0; i < currentLine.size(); i++)
	{
		if (currentLine[i] == ' ')
		{
			if (i > 0 && IsOperator(currentLine[i - 1]))
			{
				currentLine.erase(i, 1);
				i--;
			}

			else if (i < currentLine.size() - 1 && IsOperator(currentLine[i + 1]))
			{
				currentLine.erase(i, 1);
				i--;
			}
		}
		else if (currentLine[i] == '\t')
		{
			currentLine.erase(i, 1);
			i--;
		}
	}
}


bool LongPractice::IsOperator(char ch) const
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=')
		return true;

	if (ch == '&' || ch == '|' || ch == '!' || ch == '>' || ch == '<')
		return true;

	if (ch == '%' || ch == ',' || ch == ';')
		return true;

	if (ch == '(' || ch == '{' || ch == ')' || ch == '}')
		return true;

	return false;
}


void LongPractice::Main()
{
	ReadResultFile();

	RenderIntro();
	RenderPractice();
	RenderResult();

	WriteResultFile();

	mPresetCodes.clear();
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