#include"MiniGame.h"


/////////////////////////////
/* 프리셋 텍스트 파일 로드 */
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
/* 난수 테이블 생성 */
//////////////////////
void MiniGame::SetRandomTable()
{
	int temp;
	int randomIndex1;
	int randomIndex2;
	int shuffleCount = FileNum::Game * 2;						// 프리셋 파일 수의 2배만큼 반복

	for (int count = 0; count < shuffleCount; count++)			// 난수 테이블 뒤섞기 반복문
	{
		randomIndex1 = Random::Integer(0, FileNum::Game - 1);	// 무작위 인덱스 선택
		randomIndex2 = Random::Integer(0, FileNum::Game - 1);	// 무작위 인덱스 선택

		temp = mRandomTable[randomIndex1];						// 테이블 내 두 인덱스 스왑
		mRandomTable[randomIndex1] = mRandomTable[randomIndex2];
		mRandomTable[randomIndex2] = temp;
	}
}


/////////////////////////
/* 난수 테이블 값 반환 */
/////////////////////////
int MiniGame::GetRandomTableNum()
{
	mRandomTableIndex++;					// 테이블 인덱스 증가

	if (mRandomTableIndex == FileNum::Game)	// 테이블의 마지막 난수까지 사용하였다면
	{
		SetRandomTable();					// 난수 테이블을 다시 생성
		mRandomTableIndex = 0;				// 인덱스 초기화
	}

	return mRandomTable[mRandomTableIndex];	// 테이블[인덱스] 반환
}


////////////
/* 생성자 */
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
/* 행맨 그리기 */
/////////////////
void MiniGame::DrawHangman(Ending isEnding) {

	int xPosCloud = mXPosUserScript - 3;
	int yPosCloud = mYPosUserScript - 2;
	int xPosUserScript = mXPosUserScript;
	int yPosUserScript = mYPosUserScript;
	int xPosGallows = mXPosGallows;
	int yPosGallows = mYPosGallows;
	string path = "Assets/layout/minigame_cloud";

	if (isEnding == Ending::yes)			// 엔딩 화면에서는 하단에 행맨 출력
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
		mConsole->Draw("\"교수님께. 저 D0 인데 F만은 제발\"", "red", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/D0.txt", "white", xPosGallows, yPosGallows);
		break;

	case 0:
		mConsole->Draw(path, "white", xPosCloud, yPosCloud);
		mConsole->Draw("\"아! 포기하니까 이렇게 편하구나!\"", "green", xPosUserScript, yPosUserScript);
		mConsole->Draw("Assets/layout/minigame_gallows/F.txt", "white", xPosGallows, yPosGallows);
		break;
	}
}


///////////////
/* 시작 화면 */
///////////////
void MiniGame::RenderIntro()
{
	mConsole->Draw("Assets/layout/minigame_ending.txt", "white", 19, 7);
	mConsole->Draw("Hangman & C language", "white", mXPosTitleStart + 2, mYPosTitleStart);
	mConsole->Draw("MiniGame", "green", mXPosTitleStart + 7, mYPosTitleStart + 2);

	for (;;)	// 프롬프트 루프
	{
		mConsole->Draw("* Press Enter to Start *", "white", mXPosPrompt, mYPosPrompt);	// 흰색 프롬프트
		Sleep(250);

		mKeyboard->DynamicInput();			// 동적 입력 (반복문이 계속 실행되어야 하므로, 정적 입력 X)
		if (mKeyboard->IsPressed("enter"))	// 엔터가 입력되었다면
			break;							// 반복문 종료

		mConsole->Draw("* Press Enter to Start *", "yellow", mXPosPrompt, mYPosPrompt);	// 노란색 프롬프트
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;
	}

	mConsole->Clear(mXPosPrompt, mYPosPrompt, 25, 1);
	mConsole->Draw("0     0     0", "white", mXPosPrompt + 5, mYPosPrompt);

	/* 전구 활성화 */
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
/* 게임 */
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
	string presetCode;		// 프리셋 코드
	string presetAnswer;	// 프리셋 정답
	string revealAnswer;	// 밝혀진 정답
	fstream file;

	mConsole->Draw("Assets/layout/minigame_main.txt", "white", 0, 1);
	mConsole->CursorVisible(true);
	mLife = mStartLife;

	for (testNum = 0; testNum < 3 && !mQuit; testNum++)
	{
		revealCharCount = 0;
		randomIndex = GetRandomTableNum();

		presetCode = mPresetCodes[randomIndex].GetText();		// 무작위 프리셋 문제 저장
		presetAnswer = mPresetAnswers[randomIndex].GetText();	// 무작위 프리셋 문제 정답 저장

		revealAnswer.clear();
		revealAnswer.resize(presetAnswer.length(), '_');

		for (;;)
		{
			mConsole->Draw(presetCode, "white", mXPosPresetCodeStart, mYPosPresetCodeStart);	// 프리셋 출력
			mConsole->Draw(revealAnswer, "white", mXPosCout, mYPosCout);						// 밝혀진 정답 출력
			DrawHangman(Ending::no);															// 행맨 그리기

			mConsole->Clear(mXPosCin, mYPosCin, mWidthCinBox, mHeightCinBox);	// 입력 상자 비우기
			mConsole->CursorPosition(29, 41);									// 커서 위치 초기화

			cin >> inputCh;														// 문자 입력

			isCorrect = false;

			for (size_t iterAnswer = 0; iterAnswer < presetAnswer.length(); iterAnswer++)	// 정답 순회
			{
				if (inputCh == presetAnswer[iterAnswer])	// 입력한 문자와 일치한다면
				{
					presetAnswer[iterAnswer] = '\0';		// 중복 검사 방지
					revealAnswer[iterAnswer] = inputCh;		// 정답 밝히기
					revealCharCount++;

					isCorrect = true;
				}
			}

			if (isCorrect)														// 정답이라면
				mConsole->Draw("Good", "green", mXPosCorrect, mYPosCorrect);	// 초록색 상태 메시지 출력

			else																// 오답이라면
			{
				mLife--;														// 학점을 낮추고
				mConsole->Draw("Bad!", "red", mXPosCorrect, mYPosCorrect);		// 빨간색 상태 메시지 출력
			}

			mConsole->Clear(mXPosPresetCodeStart, mYPosPresetCodeStart, mWidthCodeBox, mHeightCodeBox);	// 프리셋 코드 상자 비우기
			mConsole->Clear(mXPosUserCodeStart, mYPosUserCodeStart, mWidthCodeBox, mHeightCodeBox);		// 사용자 코드 상자 비우기

			if (revealCharCount == presetAnswer.length())	// 모든 문자를 맞췄다면
				break;										// 반복문 종료

			if (mLife == 0)		// 사망하였다면
			{
				mQuit = true;	// 종료 활성화
				break;			// 반복문 종료
			}
		}

		mConsole->Clear(mXPosCout, mYPosCout, mWidthCoutBox, mHeightCoutBox);	// 출력 상자 비우기
	}

	mConsole->CursorVisible(false);
	mConsole->Clear();
	mKeyboard->Clear();
}


///////////////
/* 종료 화면 */
///////////////
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

	if (mLifeToGrade[mLife] == "A+" || mLifeToGrade[mLife] == "A0" || mLifeToGrade[mLife] == "B+" || mLifeToGrade[mLife] == "B0")	// 재수강이 불가능한 학점이라면
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
			Sleep(250);

			mKeyboard->DynamicInput();
			if (mKeyboard->IsPressed("enter"))
			{
				mQuit = true;
				break;
			}
		}
	}
	else	// 재수강이 가능한 학점이라면
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


//////////
/* 메인 */
//////////
void MiniGame::Main()
{
	RenderIntro();					// 시작 화면

	for (mQuit = false; !mQuit;)	// 게임 루프
	{
		RenderGame();				// 게임 실행
		RenderResult();				// 결과 출력
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
