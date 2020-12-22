#include"MiniGame.h"


/////////////////////////////
/* ������ �ؽ�Ʈ ���� �ε� */
/////////////////////////////
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


//////////////////////
/* ���� ���̺� ���� */
//////////////////////
void MiniGame::SetRandomTable()
{
	int temp;
	int randomIndex1;
	int randomIndex2;
	int shuffleCount = FileNum::Game * 2;						// ������ ���� ���� 2�踸ŭ �ݺ�

	for (int count = 0; count < shuffleCount; count++)			// ���� ���̺� �ڼ��� �ݺ���
	{
		randomIndex1 = Random::Integer(0, FileNum::Game - 1);	// ������ �ε��� ����
		randomIndex2 = Random::Integer(0, FileNum::Game - 1);	// ������ �ε��� ����

		temp = mRandomTable[randomIndex1];						// ���̺� �� �� �ε��� ����
		mRandomTable[randomIndex1] = mRandomTable[randomIndex2];
		mRandomTable[randomIndex2] = temp;
	}
}


/////////////////////////
/* ���� ���̺� �� ��ȯ */
/////////////////////////
int MiniGame::GetRandomTableNum()
{
	mRandomTableIndex++;					// ���̺� �ε��� ����

	if (mRandomTableIndex == FileNum::Game)	// ���̺��� ������ �������� ����Ͽ��ٸ�
	{
		SetRandomTable();					// ���� ���̺��� �ٽ� ����
		mRandomTableIndex = 0;				// �ε��� �ʱ�ȭ
	}

	return mRandomTable[mRandomTableIndex];	// ���̺�[�ε���] ��ȯ
}


////////////
/* ������ */
////////////
MiniGame::MiniGame()
{
	mRandom = Random::Instance();
	mConsole = Console::Instance();
	mKeyboard = Keyboard::Instance();

	LoadTextFiles();

	for (int count = 0; count < FileNum::Game; count++)
		mRandomTable.emplace_back(count);

	mRandomTableIndex = 0;

	SetRandomTable();
}


/////////////////
/* ��� �׸��� */
/////////////////
void MiniGame::DrawHangman(Ending isEnding) {

	int xPosCloud = mXPosUserScript - 3;
	int yPosCloud = mYPosUserScript - 2;
	int xPosUserScript = mXPosUserScript;
	int yPosUserScript = mYPosUserScript;
	int xPosGallows = mXPosGallows;
	int yPosGallows = mYPosGallows;
	string path = "Assets/layout/minigame_cloud";

	if (isEnding == Ending::yes)			// ���� ȭ�鿡���� �ϴܿ� ��� ���
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
		mConsole->Draw("\"�� ���� ����. A+ ���� ���̴�!\"", "green", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/A+.txt", "white", xPosGallows, yPosGallows);
		break;

	case 7:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"A0 �� �׷��� 4������!\"", "green", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/A0.txt", "white", xPosGallows, yPosGallows);
		break;

	case 6:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"B+ �̸� ��Ÿ�ϱ� ������\"", "blue", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/B+.txt", "white", xPosGallows, yPosGallows);
		break;

	case 5:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"B0 ������ �Ȱ� ���� ����...\"", "blue", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/B0.txt", "white", xPosGallows, yPosGallows);
		break;

	case 4:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"C+ �̶�.. ���߿� ����� �ұ�\"", "yellow", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/C+.txt", "white", xPosGallows, yPosGallows);
		break;

	case 3:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"�̰� ������ص� �Ȱ��� C0 �ϵ�...\"", "yellow", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/C0.txt", "white", xPosGallows, yPosGallows);
		break;

	case 2:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"�� D+ �̰� ����ΰ�...\"", "red", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/D+.txt", "white", xPosGallows, yPosGallows);
		break;

	case 1:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"�����Բ�. �� D0 �ε� F���� ����\"", "red", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/D0.txt", "white", xPosGallows, yPosGallows);
		break;

	case 0:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"��! �����ϴϱ� �̷��� ���ϱ���!\"", "green", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/F.txt", "white", xPosGallows, yPosGallows);
		break;
	}
}


///////////////
/* ���� ȭ�� */
///////////////
void MiniGame::RenderIntro()
{
	mConsole->Draw("Assets/layout/minigame_ending.txt", "white", 19, 7);
	mConsole->Draw("Hangman & C language", "white", mXPosTitleStart + 2, mYPosTitleStart);
	mConsole->Draw("MiniGame", "green", mXPosTitleStart + 7, mYPosTitleStart + 2);

	for (;;)	// ������Ʈ ����
	{
		mConsole->Draw("* Press Enter to Start *", "white", mXPosPrompt, mYPosPrompt);	// ��� ������Ʈ
		Sleep(250);

		mKeyboard->DynamicInput();			// ���� �Է� (�ݺ����� ��� ����Ǿ�� �ϹǷ�, ���� �Է� X)
		if (mKeyboard->IsPressed("enter"))	// ���Ͱ� �ԷµǾ��ٸ�
			break;							// �ݺ��� ����

		mConsole->Draw("* Press Enter to Start *", "yellow", mXPosPrompt, mYPosPrompt);	// ����� ������Ʈ
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;
	}

	mConsole->Clear(mXPosPrompt, mYPosPrompt, 25, 1);
	mConsole->Draw("0     0     0", "white", mXPosPrompt + 5, mYPosPrompt);

	/* ���� Ȱ��ȭ */
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

	mConsole->Clear();
	mKeyboard->Clear();
}


//////////
/* ���� */
//////////
void MiniGame::RenderGame()
{
	int testNum;
	int randomIndex;
	int revealCharCount;
	char inputCh;
	bool isCorrect;
	string path;
	string line;
	string presetCode;		// ������ �ڵ�
	string presetAnswer;	// ������ ����
	string revealAnswer;	// ������ ����
	fstream file;

	mConsole->Draw("Assets/layout/minigame_main.txt", "white", 0, 1);
	mConsole->CursorVisible(true);
	mLife = mStartLife;

	for (testNum = 0; testNum < 3 && !mQuit; testNum++)
	{
		revealCharCount = 0;
		randomIndex = GetRandomTableNum();

		presetCode = mPresetCodes[randomIndex].GetText();		// ������ ������ ���� ����
		presetAnswer = mPresetAnswers[randomIndex].GetText();	// ������ ������ ���� ���� ����

		revealAnswer.clear();
		revealAnswer.resize(presetAnswer.length(), '_');

		for (;;)
		{
			mConsole->Draw(presetCode, "white", mXPosPresetCodeStart, mYPosPresetCodeStart);	// ������ ���
			mConsole->Draw(revealAnswer, "white", mXPosCout, mYPosCout);						// ������ ���� ���
			DrawHangman(Ending::no);															// ��� �׸���

			mConsole->Clear(mXPosCin, mYPosCin, mWidthCinBox, mHeightCinBox);	// �Է� ���� ����
			mConsole->CursorPosition(29, 41);									// Ŀ�� ��ġ �ʱ�ȭ

			cin >> inputCh;														// ���� �Է�

			isCorrect = false;

			for (size_t iterAnswer = 0; iterAnswer < presetAnswer.length(); iterAnswer++)	// ���� ��ȸ
			{
				if (inputCh == presetAnswer[iterAnswer])	// �Է��� ���ڿ� ��ġ�Ѵٸ�
				{
					presetAnswer[iterAnswer] = '\0';		// �ߺ� �˻� ����
					revealAnswer[iterAnswer] = inputCh;		// ���� ������
					revealCharCount++;

					isCorrect = true;
				}
			}

			if (isCorrect)														// �����̶��
				mConsole->Draw("Good", "green", mXPosCorrect, mYPosCorrect);	// �ʷϻ� ���� �޽��� ���

			else																// �����̶��
			{
				mLife--;														// ������ ���߰�
				mConsole->Draw("Bad!", "red", mXPosCorrect, mYPosCorrect);		// ������ ���� �޽��� ���
			}

			mConsole->Clear(mXPosPresetCodeStart, mYPosPresetCodeStart, mWidthCodeBox, mHeightCodeBox);	// ������ �ڵ� ���� ����
			mConsole->Clear(mXPosUserCodeStart, mYPosUserCodeStart, mWidthCodeBox, mHeightCodeBox);		// ����� �ڵ� ���� ����

			if (revealCharCount == presetAnswer.length())	// ��� ���ڸ� ����ٸ�
				break;										// �ݺ��� ����

			if (mLife == 0)		// ����Ͽ��ٸ�
			{
				mQuit = true;	// ���� Ȱ��ȭ
				break;			// �ݺ��� ����
			}
		}

		mConsole->Clear(mXPosCout, mYPosCout, mWidthCoutBox, mHeightCoutBox);	// ��� ���� ����
	}

	mConsole->CursorVisible(false);
	mConsole->Clear();
	mKeyboard->Clear();
}


///////////////
/* ���� ȭ�� */
///////////////
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
		mConsole->Draw("B+ (��Ÿ)", "blue", mXPosTitleStart + 6, mYPosTitleStart);

	else if (mLifeToGrade[mLife] == "B0")
		mConsole->Draw("B0 (�踤)", "blue", mXPosTitleStart + 7, mYPosTitleStart);

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

	for (int x = 0; x < 3; x++)
	{
		mConsole->CursorPosition(mXPosTrafficLight + x * 6, mYPosTrafficLight);
		cout << 'y';
	}

	mConsole->Color("white");
	DrawHangman(Ending::yes);

	if (mLife > 0)
		mConsole->Draw("�������� ���߳½��ϴ�.", "white", mXPosTitleStart, mYPosTitleStart + 2);
	else
		mConsole->Draw("C++ �� öȸ�Ͽ����ϴ�.", "white", mXPosTitleStart, mYPosTitleStart + 2);

	if (mLifeToGrade[mLife] == "A+" || mLifeToGrade[mLife] == "A0" || mLifeToGrade[mLife] == "B+" || mLifeToGrade[mLife] == "B0")	// ������� �Ұ����� �����̶��
	{
		for (;;)
		{
			if (mLifeToGrade[mLife] == "A+" || mLifeToGrade[mLife] == "A0")
				mConsole->Draw("* ���������� �����Ѵ� *", "white", mXPosPrompt, mYPosPrompt);
			else
				mConsole->Draw("* �ָ������� �Ѿ�� *", "white", mXPosPrompt, mYPosPrompt);

			mConsole->Draw("y", "random", mXPosTrafficLight, mYPosTrafficLight);
			mConsole->Draw("y", "random", mXPosTrafficLight + 6, mYPosTrafficLight);
			mConsole->Draw("y", "random", mXPosTrafficLight + 12, mYPosTrafficLight);
			Sleep(250);

			mKeyboard->DynamicInput();
			if (mKeyboard->IsPressed("enter"))
			{
				mQuit = true;
				break;
			}

			if (mLifeToGrade[mLife] == "A+" || mLifeToGrade[mLife] == "A0")
				mConsole->Draw("* ���������� �����Ѵ� *", "yellow", mXPosPrompt, mYPosPrompt);
			else
				mConsole->Draw("* �ָ������� �Ѿ�� *", "yellow", mXPosPrompt, mYPosPrompt);

			mConsole->Draw("y", "random", mXPosTrafficLight, mYPosTrafficLight);
			mConsole->Draw("y", "random", mXPosTrafficLight + 6, mYPosTrafficLight);
			mConsole->Draw("y", "random", mXPosTrafficLight + 12, mYPosTrafficLight);
			Sleep(250);

			mKeyboard->DynamicInput();
			if (mKeyboard->IsPressed("enter"))
			{
				mQuit = true;
				break;
			}
		}
	}
	else	// ������� ������ �����̶��
	{
		for (int menu = 0;;)
		{
			mConsole->Clear(mXPosPrompt, mYPosPrompt, 24, 1);
			mConsole->Draw("   �����       ���", "white", mXPosPrompt, mYPosPrompt);

			if (menu == 0)
				mConsole->Draw("-> ����� <-", "green", mXPosPrompt, mYPosPrompt);

			else if (menu == 1)
				mConsole->Draw("-> ��� <-", "red", mXPosPrompt + 13, mYPosPrompt);

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


//////////
/* ���� */
//////////
void MiniGame::Main()
{
	RenderIntro();					// ���� ȭ��

	for (mQuit = false; !mQuit;)	// ���� ����
	{
		RenderGame();				// ���� ����
		RenderResult();				// ��� ���
	}
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
