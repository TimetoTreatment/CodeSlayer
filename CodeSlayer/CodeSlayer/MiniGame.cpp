#include"MiniGame.h"


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
	
	int cnt;
	char input;
	int testNum;

	string path;
	string line;
	string presetCode;
	string presetAnswer;
	string revealAnswer;
	fstream file;

	int randomIndex;

	mConsole->Draw("Assets/layout/minigame_main.txt", "white", 0, 1);
	mLife = mStartLife;

	for (testNum = 0; testNum < 3 && !mQuit; testNum++)
	{
		cnt = 0;

		randomIndex = mRandom->Integer(0, FileNum::Game - 1);

		path = "Assets/preset/Game/game" + to_string(randomIndex) + ".txt";
		file.open(path);

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
		file.close();

		path = "Assets/preset/Game_Ans/gameAns" + to_string(randomIndex) + ".txt";
		file.open(path);

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
		file.close();

		revealAnswer.clear();
		revealAnswer.resize(presetAnswer.length(), '_');

		while (1)
		{
			mConsole->Draw(presetCode, "white", mXPosPresetCodeStart, mYPosPresetCodeStart);
			DrawHangman(false);

			mConsole->Draw(revealAnswer, "white", mXPosCout, mYPosCout);

			mConsole->Clear(mXPosCin, mYPosCin, mWidthCinBox, mHeightCinBox);
			mConsole->CursorPosition(29, 41);

			cin >> input;

			bool Good = false;

			for (int j = 0; j < presetAnswer.length(); j++) {
				if (IsCorrect(input, presetAnswer[j], &revealAnswer[j]) == true) {
					presetAnswer[j] = NULL;
					revealAnswer[j] = input;
					cnt++;
					Good = true;
				}
			}
			if (Good == true) {
				mConsole->Draw("Good", "green", mXPosCorrect, mYPosCorrect);
			}
			else {
				mLife--;
				mConsole->Draw("Bad!", "red", mXPosCorrect, mYPosCorrect);
			}

			//-------------------------------------------------------------------------------------//

			mConsole->Clear(mXPosPresetCodeStart, mYPosPresetCodeStart, mWidthCodeBox, mHeightCodeBox);
			mConsole->Clear(mXPosUserCodeStart, mYPosUserCodeStart, mWidthCodeBox, mHeightCodeBox);

			if (cnt == presetAnswer.length())
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
		mConsole->Draw("A+ (�ְ�)", "green", mXPosTitleStart + 6, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "A0")
		mConsole->Draw("A0 (����)", "green", mXPosTitleStart + 6, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "B+")
		mConsole->Draw("B+ (��Ÿ)", "white", mXPosTitleStart + 6, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "B0")
		mConsole->Draw("B0 (�踤)", "white", mXPosTitleStart + 7, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "C+")
		mConsole->Draw("C+ (�ָ�)", "yellow", mXPosTitleStart + 7, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "C0")
		mConsole->Draw("C0 (�Ҹ�)", "yellow", mXPosTitleStart + 7, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "D+")
		mConsole->Draw("D+ (����)", "red", mXPosTitleStart + 7, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "D0")
		mConsole->Draw("D0 (��¦)", "red", mXPosTitleStart + 7, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "F")
		mConsole->Draw("F (���)", "red", mXPosTitleStart + 7, mYPosTitleStart);

	mConsole->Color("white");
	DrawHangman(true);

	if (mLife > 0)
		mConsole->Draw("�������� ���߳½��ϴ�.", "white", mXPosTitleStart, mYPosTitleStart + 2);
	else
		mConsole->Draw("C++ �� ����Ͽ����ϴ�.", "white", mXPosTitleStart, mYPosTitleStart + 2);

	int menu = 0;

	for (;;)
	{
		mConsole->Clear(mXPosPrompt, mYPosPrompt, 24, 1);
		mConsole->Draw("   �����       öȸ", "white", mXPosPrompt, mYPosPrompt);

		if (menu == 0)
			mConsole->Draw("-> ����� <-", "green", mXPosPrompt, mYPosPrompt);

		else if (menu == 1)
			mConsole->Draw("-> öȸ <-", "red", mXPosPrompt + 13, mYPosPrompt);

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


bool MiniGame::IsCorrect(char input, char text, char* Answer) {

	if (text == input) {
		*Answer = input;
		return true;
	}

	return false;
}

void MiniGame::DrawHangman(bool isEnding) {

	int xPosCloud = mXPosUserScript - 3;
	int yPosCloud = mYPosUserScript - 2;
	int xPosUserScript = mXPosUserScript;
	int yPosUserScript = mYPosUserScript;
	int xPosGallows = mXPosGallows;
	int yPosGallows = mYPosGallows;

	if (isEnding == true)
	{
		xPosCloud = mXPosEnding;
		yPosCloud = mYPosEnding - 2;
		xPosUserScript = mXPosEnding + 3;
		yPosUserScript = mYPosEnding;
		xPosGallows = mXPosEnding;
		yPosGallows = mYPosEnding + 3;
	}

	switch (mLife)
	{
	case 8:
		mConsole->Draw("Assets/layout/minigame_cloud.txt", "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"�� ���� ����. A+ ���� ���̴�!\"", "green", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/A+.txt", "white", xPosGallows, yPosGallows);
		break;

	case 7:
		mConsole->Draw("Assets/layout/minigame_cloud.txt", "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"A0 �� �׷��� 4������!\"", "green", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/A0.txt", "white", xPosGallows, yPosGallows);
		break;

	case 6:
		mConsole->Draw("Assets/layout/minigame_cloud.txt", "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"B+ �̸� ��Ÿ�ϱ� ������\"", "yellow", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/B+.txt", "white", xPosGallows, yPosGallows);
		break;

	case 5:
		mConsole->Draw("Assets/layout/minigame_cloud.txt", "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"B0 ������ �Ȱ� ���� ����...\"", "yellow", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/B0.txt", "white", xPosGallows, yPosGallows);
		break;

	case 4:
		mConsole->Draw("Assets/layout/minigame_cloud.txt", "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"C+ �̶�.. ���߿� ����� �ұ�\"", "blue", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/C+.txt", "white", xPosGallows, yPosGallows);
		break;

	case 3:
		mConsole->Draw("Assets/layout/minigame_cloud.txt", "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"�̰� ������ص� �Ȱ��� C0 �ϵ�...\"", "blue", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/C0.txt", "white", xPosGallows, yPosGallows);
		break;

	case 2:
		mConsole->Draw("Assets/layout/minigame_cloud.txt", "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"�� D+ �̰� ����ΰ�...\"", "red", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/D+.txt", "white", xPosGallows, yPosGallows);
		break;

	case 1:
		mConsole->Draw("Assets/layout/minigame_cloud.txt", "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"To ����. �� D0 �ε� F���� ����\"", "red", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/D0.txt", "white", xPosGallows, yPosGallows);
		break;

	case 0:
		mConsole->Draw("Assets/layout/minigame_cloud.txt", "white", mXPosEnding, mYPosEnding - 2);
		mConsole->Draw("\"��! �����ϴϱ� �̷��� ���ϱ���!\"", "green", mXPosEnding + 3, mYPosEnding);
		mConsole->Draw("Assets/layout/minigame_gallows/F.txt", "white", mXPosEnding, mYPosEnding + 3);
		break;
	}
}


MiniGame::MiniGame() {

	mRandom = Random::Instance();
	mConsole = Console::Instance();
	mKeyboard = Keyboard::Instance();
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
