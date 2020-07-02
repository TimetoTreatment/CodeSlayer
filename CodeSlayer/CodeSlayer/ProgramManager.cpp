#include "ProgramManager.h"

ProgramManager::ProgramManager()
{
	mConsole = Console::Instance();				// 보조 클래스 객체 생성
	mRandom = Random::Instance();				//
	mKeyboard = Keyboard::Instance();			//
	mMouse = Mouse::Instance();					//
	mUserAnalysis = UserAnalysis::Instance();	//

	mMainMenu = MainMenu::Instance();			// 주 클래스 객체 생성
	mWordPractice = WordPractice::Instance();	//
	mShortPractice = ShortPractice::Instance();	//
	mLongPractice = LongPractice::Instance();	//
	mStatistics = Statistics::Instance();		//
	mMiniGame = MiniGame::Instance();			//

	mCurrentScreen = Screen::MainMenu;			// 현재 화면을 메인 메뉴로 초기화
	mQuit = false;
}


ProgramManager::~ProgramManager()
{
	mConsole->Release();		// 보조 클래스 객체 소멸
	mRandom->Release();			//
	mKeyboard->Release();		//
	mMouse->Release();			//
	mUserAnalysis->Release();	//

	mMainMenu->Release();		// 주 클래스 객체 소멸
	mWordPractice->Release();	//
	mShortPractice->Release();	//
	mLongPractice->Release();	//
	mStatistics->Release();		//
	mMiniGame->Release();		//
}


///////////////
/* 소개 화면 */
///////////////
void ProgramManager::IntroScreen()
{
	Sleep(100);	// 1000
	mConsole->Draw("Assets/layout/intro_teamLogo.txt", "white", mXPosTeamLogo, mYPosTeamLogo);
	mConsole->Draw("Assets/layout/intro_teamBoard.txt", "white", mXPosTeamBoard, mYPosTeamBoard);
	mConsole->Draw("Assets/layout/intro_teamMember.txt", "white", mXPosTeamMember, mYPosTeamMember);
	Sleep(200);	// 2000
	mConsole->Draw("Assets/layout/intro_programLogo.txt", "blue", mXPosProgramLogo, mYPosProgramLogo);
	Sleep(200);	// 2000

	mConsole->Clear(mXPosTeamBoardBox, mYPosTeamBoardBox, mWidthTeamBoard, mHeightTeamBoard);

	for (;;)		// 프롬프트 루프
	{
		mConsole->Draw("* Press Enter to Start *", "white", mXPosPrompt, mYPosPrompt);	// 흰색 프롬프트
		Sleep(250);

		mKeyboard->DynamicInput();			// 동적 입력 (반복문이 계속 실행되어야 하므로, 정적 입력 X)
		if (mKeyboard->IsPressed("enter"))	// 엔터가 입력되었다면
			break;							// 반복문 종료

		mConsole->Draw("* Press Enter to Start *", "blue", mXPosPrompt, mYPosPrompt);	// 파란색 프롬프트
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;
	}

	mConsole->Clear();		// 화면 지우기
	mKeyboard->Clear();		// 키보드 입력 초기화 (프롬프트 루프에서 입력한 엔터 삭제)
}


///////////////
/* 종료 화면 */
///////////////
void ProgramManager::ExitScreen()
{
	mConsole->Draw("Assets/layout/intro_teamLogo.txt", "white", mXPosTeamLogo, mYPosTeamLogo);
	mConsole->Draw("Assets/layout/intro_teamBoard.txt", "white", mXPosTeamBoard, mYPosTeamBoard);
	mConsole->Draw("Assets/layout/intro_programLogo.txt", "blue", mXPosProgramLogo, mYPosProgramLogo);

	mConsole->Draw("Shutting Down CodeSlayer.", "white", mXPosPrompt - 1, mYPosPrompt);
	Sleep(500);

	mConsole->Draw("Shutting Down CodeSlayer..", "white", mXPosPrompt - 1, mYPosPrompt);
	Sleep(500);

	mConsole->Draw("Shutting Down CodeSlayer...", "white", mXPosPrompt - 1, mYPosPrompt);
	Sleep(500);

	mConsole->Draw("Shutting Down CodeSlayer...", "blue", mXPosPrompt - 1, mYPosPrompt);
	Sleep(1000);

	mConsole->CursorPosition(0, 40);
	mConsole->Color("default");
}


///////////////
/* 메인 루프 */
///////////////
void ProgramManager::MainLoop()
{
	system("mode CON: COLS=130 LINES=45");	// 콘솔 크기 조절 (120, 30) -> (130, 45)
	IntroScreen();							// 시작 화면 출력

	for (; !mQuit;)
	{
		mMainMenu->Main();							// 메인 메뉴 클래스 실행
		mCurrentScreen = mMainMenu->NextScreen();	// 사용자가 호출한 기능 업데이트

		switch (mCurrentScreen)		// 사용자가 호출한 기능
		{
		case Screen::WordPractice:	// 단어연습
			mWordPractice->Main();
			break;

		case Screen::ShortPractice:	// 짧은 글 연습
			mShortPractice->Main();
			break;

		case Screen::LongPractice:	// 긴 글 연습
			mLongPractice->Main();
			break;

		case Screen::Statistics:	// 통계
			mStatistics->Main();
			break;

		case Screen::MiniGame:		// 미니 게임
			mMiniGame->Main();
			break;

		case Screen::Exit:			// 종료
			mQuit = true;
			break;
		}

		mConsole->Clear();		// 화면 비우기
		mKeyboard->Clear();		// 키보드 입력 초기화
	}

	ExitScreen();	// 종료 화면 출력
}


ProgramManager* ProgramManager::sInstance = nullptr;

ProgramManager* ProgramManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new ProgramManager;

	return sInstance;
}

void ProgramManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}
