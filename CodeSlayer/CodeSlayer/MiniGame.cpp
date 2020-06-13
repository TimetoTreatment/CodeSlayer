#include"MiniGame.h"


void MiniGame::LoadTextFiles()
{
	Text newText;
	string path;
	string line;
	string presetCode;
	string presetAnswer;
	fstream file;

	for (int fileCount = 0; fileCount < FileNum::Game; fileCount++)
	{
		path = "Assets/preset/game/game" + to_string(fileCount) + ".txt";
		file.open(path, ios::in);

		if (!file.good())
		{
			cout << "Cannot Open " << path;
			exit(-1);
		}

		for (presetCode.clear(); !file.eof();)
		{
			getline(file, line);
			presetCode += line + '\n';
		}

		newText.SetText(presetCode);

		mPresetCodes.emplace_back(newText);
		file.close();

		path = "Assets/preset/game_answer/gameAns" + to_string(fileCount) + ".txt";
		file.open(path, ios::in);

		if (!file.good())
		{
			cout << "Cannot Open " << path;
			exit(-1);
		}

		for (presetAnswer.clear(); !file.eof();)
		{
			getline(file, line);
			presetAnswer += line;
		}

		newText.SetText(presetAnswer);

		mPresetAnswers.emplace_back(newText);
		file.close();
	}
}


void MiniGame::SetRandomTable()
{
	int temp;
	int randomIndex1;
	int randomIndex2;
	int shuffleCount = FileNum::Game * 2;

	for (int count = 0; count < shuffleCount; count++)
	{
		randomIndex1 = Random::Integer(0, FileNum::Game - 1);
		randomIndex2 = Random::Integer(0, FileNum::Game - 1);

		temp = mRandomTable[randomIndex1];
		mRandomTable[randomIndex1] = mRandomTable[randomIndex2];
		mRandomTable[randomIndex2] = temp;
	}
}


int MiniGame::GetRandomTableNum()
{
	mRandomTableIndex++;

	if (mRandomTableIndex == FileNum::Game)
	{
		SetRandomTable();
		mRandomTableIndex = 0;
	}

	return mRandomTable[mRandomTableIndex];
}


void MiniGame::RenderIntro()
{
	mConsole->Draw("Assets/layout/minigame_ending.txt", "white", 19, 7);
	mConsole->Draw("Hangman & Cplusplus", "white", mXPosTitleStart + 2, mYPosTitleStart);
	mConsole->Draw("MiniGame", "green", mXPosTitleStart + 7, mYPosTitleStart + 2);

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

	mConsole->Clear();
	mKeyboard->Clear();
}


void MiniGame::RenderGame()
{
	int testNum;
	int randomIndex;
	int revealCharCount;
	char inputCh;
	bool isCorrect;
	string path;
	string line;
	string presetCode;
	string presetAnswer;
	string revealAnswer;
	fstream file;

	mConsole->Draw("Assets/layout/minigame_main.txt", "white", 0, 1);
	mLife = mStartLife;

	for (testNum = 0; testNum < 3 && !mQuit; testNum++)
	{
		revealCharCount = 0;
		randomIndex = GetRandomTableNum();

		presetAnswer = mPresetAnswers[randomIndex].GetText();
		presetCode = mPresetCodes[randomIndex].GetText();

		revealAnswer.clear();
		revealAnswer.resize(presetAnswer.length(), '_');

		for (;;)
		{
			mConsole->Draw(presetCode, "white", mXPosPresetCodeStart, mYPosPresetCodeStart);
			mConsole->Draw(revealAnswer, "white", mXPosCout, mYPosCout);
			DrawHangman(Ending::no);

			mConsole->Clear(mXPosCin, mYPosCin, mWidthCinBox, mHeightCinBox);
			mConsole->CursorPosition(29, 41);

			cin >> inputCh;

			isCorrect = false;

			for (size_t iterAnswer = 0; iterAnswer < presetAnswer.length(); iterAnswer++)
			{
				if (inputCh == presetAnswer[iterAnswer])
				{
					presetAnswer[iterAnswer] = '\0';
					revealAnswer[iterAnswer] = inputCh;
					revealCharCount++;

					isCorrect = true;
				}
			}

			if (isCorrect)
				mConsole->Draw("Good", "green", mXPosCorrect, mYPosCorrect);
			else
			{
				mLife--;
				mConsole->Draw("Bad!", "red", mXPosCorrect, mYPosCorrect);
			}

			mConsole->Clear(mXPosPresetCodeStart, mYPosPresetCodeStart, mWidthCodeBox, mHeightCodeBox);
			mConsole->Clear(mXPosUserCodeStart, mYPosUserCodeStart, mWidthCodeBox, mHeightCodeBox);

			if (revealCharCount == presetAnswer.length())
				break;

			if (mLife == 0)
			{
				mQuit = true;
				break;
			}
		}

		mConsole->Clear(mXPosCout, mYPosCout, mWidthCoutBox, mHeightCoutBox);
	}

	mConsole->Clear();
	mKeyboard->Clear();
}


void MiniGame::RenderResult()
{
	mConsole->Clear();
	mKeyboard->Clear();

	mConsole->Draw("Assets/layout/minigame_ending.txt", "white", 19, 7);

	if (mLifeToGrade[mLife] == "A+")
		mConsole->Draw("A+ (최고)", "green", mXPosTitleStart + 6, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "A0")
		mConsole->Draw("A0 (만족)", "green", mXPosTitleStart + 6, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "B+")
		mConsole->Draw("B+ (평타)", "blue", mXPosTitleStart + 6, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "B0")
		mConsole->Draw("B0 (계륵)", "blue", mXPosTitleStart + 7, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "C+")
		mConsole->Draw("C+ (애매)", "yellow", mXPosTitleStart + 7, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "C0")
		mConsole->Draw("C0 (불만)", "yellow", mXPosTitleStart + 7, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "D+")
		mConsole->Draw("D+ (망함)", "red", mXPosTitleStart + 7, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "D0")
		mConsole->Draw("D0 (관짝)", "red", mXPosTitleStart + 7, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "F")
		mConsole->Draw("F (사망)", "red", mXPosTitleStart + 7, mYPosTitleStart);

	for (int x = 0; x < 3; x++)
	{
		mConsole->CursorPosition(mXPosTrafficLight + x * 6, mYPosTrafficLight);
		cout << 'y';
	}

	mConsole->Color("white");
	DrawHangman(Ending::yes);

	if (mLife > 0)
		mConsole->Draw("종강까지 버텨냈습니다.", "white", mXPosTitleStart, mYPosTitleStart + 2);
	else
		mConsole->Draw("C++ 을 철회하였습니다.", "white", mXPosTitleStart, mYPosTitleStart + 2);


	if (mLifeToGrade[mLife] == "A+" || mLifeToGrade[mLife] == "A0" || mLifeToGrade[mLife] == "B+" || mLifeToGrade[mLife] == "B0")
	{
		for (;;)
		{
			if (mLifeToGrade[mLife] == "A+" || mLifeToGrade[mLife] == "A0")
				mConsole->Draw("* 만족스럽게 종강한다 *", "white", mXPosPrompt, mYPosPrompt);
			else
				mConsole->Draw("* 애매하지만 넘어간다 *", "white", mXPosPrompt, mYPosPrompt);

			mConsole->Draw("y", "random", mXPosTrafficLight, mYPosTrafficLight);
			mConsole->Draw("y", "random", mXPosTrafficLight + 6, mYPosTrafficLight);
			mConsole->Draw("y", "random", mXPosTrafficLight + 12, mYPosTrafficLight);
			mConsole->CursorPosition(0, 0);
			Sleep(250);

			mKeyboard->DynamicInput();
			if (mKeyboard->IsPressed("enter"))
			{
				mQuit = true;
				break;
			}

			if (mLifeToGrade[mLife] == "A+" || mLifeToGrade[mLife] == "A0")
				mConsole->Draw("* 만족스럽게 종강한다 *", "yellow", mXPosPrompt, mYPosPrompt);
			else
				mConsole->Draw("* 애매하지만 넘어간다 *", "yellow", mXPosPrompt, mYPosPrompt);

			mConsole->Draw("y", "random", mXPosTrafficLight, mYPosTrafficLight);
			mConsole->Draw("y", "random", mXPosTrafficLight + 6, mYPosTrafficLight);
			mConsole->Draw("y", "random", mXPosTrafficLight + 12, mYPosTrafficLight);
			mConsole->CursorPosition(0, 0);
			Sleep(250);

			mKeyboard->DynamicInput();
			if (mKeyboard->IsPressed("enter"))
			{
				mQuit = true;
				break;
			}
		}
	}
	else
	{
		for (int menu = 0;;)
		{
			mConsole->Clear(mXPosPrompt, mYPosPrompt, 24, 1);
			mConsole->Draw("   재수강       드랍", "white", mXPosPrompt, mYPosPrompt);

			if (menu == 0)
				mConsole->Draw("-> 재수강 <-", "green", mXPosPrompt, mYPosPrompt);

			else if (menu == 1)
				mConsole->Draw("-> 드랍 <-", "red", mXPosPrompt + 13, mYPosPrompt);

			mKeyboard->StaticInput();

			if (mKeyboard->IsPressed("enter"))
			{
				if (menu == 0)
					mQuit = false;
				else if (menu == 1)
					mQuit = true;

				break;
			}

			else if (mKeyboard->IsPressed("up") || mKeyboard->IsPressed("left"))
			{
				menu--;

				if (menu < 0)
					menu = 1;
			}
			else if (mKeyboard->IsPressed("down") || mKeyboard->IsPressed("right"))
			{
				menu++;

				if (menu > 1)
					menu = 0;
			}
		}
	}

	mConsole->Clear();
	mKeyboard->Clear();
}


void MiniGame::Main()
{
	RenderIntro();

	for (mQuit = false; !mQuit;)
	{
		RenderGame();
		RenderResult();
	}
}


void MiniGame::DrawHangman(Ending isEnding) {

	int xPosCloud = mXPosUserScript - 3;
	int yPosCloud = mYPosUserScript - 2;
	int xPosUserScript = mXPosUserScript;
	int yPosUserScript = mYPosUserScript;
	int xPosGallows = mXPosGallows;
	int yPosGallows = mYPosGallows;
	string path = "Assets/layout/minigame_cloud";

	if (isEnding == Ending::yes)
	{
		xPosCloud = mXPosEnding - 41;
		yPosCloud = mYPosEnding - 2;
		xPosUserScript = mXPosEnding - 38;
		yPosUserScript = mYPosEnding;
		xPosGallows = mXPosEnding;
		yPosGallows = mYPosEnding;
		path += "_ending";
	}

	path += ".txt";

	switch (mLife)
	{
	case 8:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"오 정말 쉽군. A+ 공장 각이다!\"", "green", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/A+.txt", "white", xPosGallows, yPosGallows);
		break;

	case 7:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"A0 면 그래도 4점대지!\"", "green", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/A0.txt", "white", xPosGallows, yPosGallows);
		break;

	case 6:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"B+ 이면 평타니까 괜찮아\"", "blue", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/B+.txt", "white", xPosGallows, yPosGallows);
		break;

	case 5:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"B0 정도면 안고 갈만 하지...\"", "blue", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/B0.txt", "white", xPosGallows, yPosGallows);
		break;

	case 4:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"C+ 이라.. 나중에 재수강 할까\"", "yellow", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/C+.txt", "white", xPosGallows, yPosGallows);
		break;

	case 3:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"이건 재수강해도 똑같이 C0 일듯...\"", "yellow", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/C0.txt", "white", xPosGallows, yPosGallows);
		break;

	case 2:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"와 D+ 이게 사람인가...\"", "red", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/D+.txt", "white", xPosGallows, yPosGallows);
		break;

	case 1:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"To 교수. 저 D0 인데 F만은 제발\"", "red", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/D0.txt", "white", xPosGallows, yPosGallows);
		break;

	case 0:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"아! 포기하니까 이렇게 편하구나!\"", "green", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/F.txt", "white", xPosGallows, yPosGallows);
		break;
	}
}


MiniGame::MiniGame() {

	mRandom = Random::Instance();
	mConsole = Console::Instance();
	mKeyboard = Keyboard::Instance();

	LoadTextFiles();

	for (int count = 0; count < FileNum::Game; count++)
		mRandomTable.emplace_back(count);

	mRandomTableIndex = 0;

	SetRandomTable();
}


MiniGame* MiniGame::sInstance = nullptr;

MiniGame* MiniGame::Instance()
{
	if (sInstance == nullptr)
		sInstance = new MiniGame;

	return sInstance;
}

void MiniGame::Release()
{
	delete sInstance;
	sInstance = nullptr;
}
