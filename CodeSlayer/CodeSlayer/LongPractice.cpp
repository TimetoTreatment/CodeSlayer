#include "LongPractice.h"


LongPractice::LongPractice()
{
	mConsole = Console::Instance();
	mKeyboard = Keyboard::Instance();
	mTimer = new Timer;
	mPresetCodes.reserve(100);
	mRecentResultNum = 0;
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
	string persetCode;
	string userLine;
	string userLineOrganized;
	string presetLine;
	size_t prePos, pos;
	size_t currentLine;
	size_t indentation;
	size_t CurrentIndentation;

	mConsole->Clear();
	mConsole->Draw("Assets/layout/longpractice_main.txt", "white", 0, 1);
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

			mConsole->Color("white");
			mConsole->CursorPosition(mXPosUserCodeStart, mYPosUserCodeStart + currentLine);
			indentation = OrganizeCode(presetLine);

			for (CurrentIndentation = 0; CurrentIndentation < indentation; CurrentIndentation++)
				cout << " ";

			getline(cin, userLine);

			mPresetTotalCh += presetLine.size();
			mUserTotalCh += userLine.size();
			mTypingSpeed = (int)(mUserTotalCh / mTimer->GetElapsedTime() * 60);

			userLineOrganized = userLine;

			OrganizeCode(userLineOrganized);

			if (presetLine == userLineOrganized)
			{
				mConsole->Draw(userLine, "green", mXPosUserCodeStart + indentation, mYPosUserCodeStart + currentLine);
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

				mConsole->Draw(userLine, "red", mXPosUserCodeStart + indentation, mYPosUserCodeStart + currentLine);
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

	mPresetCodes.clear();
}


void LongPractice::RenderResult()
{
	mConsole->Clear();
	mKeyboard->Clear();

	mConsole->Draw("Assets/layout/longpractice_intro.txt", "white", 19, 7);
	mConsole->Draw("Speed : ", "white", 58, 10);

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


size_t LongPractice::OrganizeCode(string& currentline)
{
	size_t indentation;
	size_t i = 0;

	for (indentation = 0; indentation < currentline.size(); indentation++)
	{
		if (currentline[indentation] != ' ' && currentline[indentation] != '\t')
			break;
	}

	currentline.erase(0, indentation);

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

	return indentation;
}


bool LongPractice::IsOperator(char ch)
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
	mConsole->Clear();
	mKeyboard->Clear();

	ReadResultFile();
	RenderIntro();
	RenderPractice();
	RenderResult();
	WriteResultFile();

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