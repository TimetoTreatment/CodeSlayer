#include "MainMenu.h"

void operator++(MainMenu::GeneralMenu& lhs, int)
{
	switch (lhs)
	{
	case MainMenu::GeneralMenu::TypingPractice: lhs = MainMenu::GeneralMenu::MiniGame;          break;
	case MainMenu::GeneralMenu::MiniGame:       lhs = MainMenu::GeneralMenu::Exit;              break;
	case MainMenu::GeneralMenu::Exit:           lhs = MainMenu::GeneralMenu::TypingPractice;    break;
	}
}

void operator--(MainMenu::GeneralMenu& lhs, int)
{
	switch (lhs)
	{
	case MainMenu::GeneralMenu::TypingPractice: lhs = MainMenu::GeneralMenu::Exit;              break;
	case MainMenu::GeneralMenu::MiniGame:       lhs = MainMenu::GeneralMenu::TypingPractice;    break;
	case MainMenu::GeneralMenu::Exit:           lhs = MainMenu::GeneralMenu::MiniGame;          break;
	}
}

void operator++(MainMenu::PracticeMenu& lhs, int)
{
	switch (lhs)
	{
	case MainMenu::PracticeMenu::Word:      lhs = MainMenu::PracticeMenu::Short;        break;
	case MainMenu::PracticeMenu::Short:     lhs = MainMenu::PracticeMenu::Long;         break;
	case MainMenu::PracticeMenu::Long:      lhs = MainMenu::PracticeMenu::Statistics;   break;
	case MainMenu::PracticeMenu::Statistics:lhs = MainMenu::PracticeMenu::Back;         break;
	case MainMenu::PracticeMenu::Back:      lhs = MainMenu::PracticeMenu::Word;         break;
	}
}

void operator--(MainMenu::PracticeMenu& lhs, int)
{
	switch (lhs)
	{
	case MainMenu::PracticeMenu::Word:      lhs = MainMenu::PracticeMenu::Back;         break;
	case MainMenu::PracticeMenu::Short:     lhs = MainMenu::PracticeMenu::Word;         break;
	case MainMenu::PracticeMenu::Long:      lhs = MainMenu::PracticeMenu::Short;        break;
	case MainMenu::PracticeMenu::Statistics:lhs = MainMenu::PracticeMenu::Long;         break;
	case MainMenu::PracticeMenu::Back:      lhs = MainMenu::PracticeMenu::Statistics;   break;
	}
}


MainMenu::MainMenu()
{
	mConsole = Console::Instance();
	mKeyboard = Keyboard::Instance();
	mMouse = Mouse::Instance();

	mSelectGeneralMenu = GeneralMenu::TypingPractice;
	mSelectPracticeMenu = PracticeMenu::Word;

	mNextScreen = Screen::MainMenu;
	mMoveScreen = false;
}


MainMenu::~MainMenu()
{

}


///////////////////
/* 레이아웃 출력 */
///////////////////
void MainMenu::RenderLayout()
{
	mConsole->Draw("Assets/layout/intro_programLogo.txt", "blue", 10, 5);   // 프로그램 로고
	mConsole->Draw("Assets/layout/mainmenu_brickwall.txt", "white", 6, 17); // 벽돌 벽
}


//////////////////
/* Phase 1 메뉴 */
//////////////////
void MainMenu::RenderGeneralMenu()
{
	for (bool quit = false;;)
	{
		/* 모든 항목을 흰색으로 출력 */
		mConsole->Draw("Typing Practice", "white", mXPosTypingPractice, mYPosTypingPractice);
		mConsole->Draw("MiniGame", "white", mXPosMiniGame, mYPosMiniGame);
		mConsole->Draw("Exit", "white", mXPosExit, mYPosExit);

		switch (mSelectGeneralMenu)                                                             // 현재 선택한 메뉴   
		{
		case GeneralMenu::TypingPractice:                                                       // 타자 연습
			mConsole->Draw("Typing Practice", "red", mXPosTypingPractice, mYPosTypingPractice); // 색상 변경
			break;

		case GeneralMenu::MiniGame:
			mConsole->Draw("MiniGame", "green", mXPosMiniGame, mYPosMiniGame);
			break;

		case GeneralMenu::Exit:
			mConsole->Draw("Exit", "blue", mXPosExit, mYPosExit);
			break;
		}

		for (mKeyboard->Clear();;)
		{
			mKeyboard->DynamicInput();               // 화살표 키 또는 엔터 키 대기

			if (mKeyboard->IsPressed("up"))         // 화살표 위
			{
				mSelectGeneralMenu--;               // 이전 메뉴
				break;
			}

			else if (mKeyboard->IsPressed("down"))  // 화살표 아래
			{
				mSelectGeneralMenu++;               // 다음 메뉴
				break;
			}

			else if (mKeyboard->IsPressed("enter")) // 엔터
			{
				quit = true;
				break;                              // 반복문 종료
			}

			mMouse->DynamicClick();
			mMouse->DynamicScan();

			if (mMouse->XPosScan() > mXPosTypingPracticeHitboxLT && mMouse->XPosScan() < mXPosTypingPracticeHitboxRB && mMouse->YPosScan() > mYPosTypingPracticeHitboxLT && mMouse->YPosScan() < mYPosTypingPracticeHitboxRB)
			{
				if (mSelectGeneralMenu != GeneralMenu::TypingPractice)
				{
					mConsole->Draw("Typing Practice", "red", mXPosTypingPractice, mYPosTypingPractice);
					mConsole->Draw("MiniGame", "white", mXPosMiniGame, mYPosMiniGame);
					mConsole->Draw("Exit", "white", mXPosExit, mYPosExit);
				}

				mSelectGeneralMenu = GeneralMenu::TypingPractice;
			}

			else if (mMouse->XPosScan() > mXPosMiniGameHitboxLT && mMouse->XPosScan() < mXPosMiniGameHitboxRB && mMouse->YPosScan() > mYPosMiniGameHitboxLT && mMouse->YPosScan() < mYPosMiniGameHitboxRB)
			{
				if (mSelectGeneralMenu != GeneralMenu::MiniGame)
				{
					mConsole->Draw("Typing Practice", "white", mXPosTypingPractice, mYPosTypingPractice);
					mConsole->Draw("MiniGame", "green", mXPosMiniGame, mYPosMiniGame);
					mConsole->Draw("Exit", "white", mXPosExit, mYPosExit);
				}

				mSelectGeneralMenu = GeneralMenu::MiniGame;
			}

			else if (mMouse->XPosScan() > mXPosExitHitboxLT && mMouse->XPosScan() < mXPosExitHitboxRB && mMouse->YPosScan() > mYPosExitHitboxLT && mMouse->YPosScan() < mYPosExitHitboxRB)
			{
				if (mSelectGeneralMenu != GeneralMenu::Exit)
				{
					mConsole->Draw("Typing Practice", "white", mXPosTypingPractice, mYPosTypingPractice);
					mConsole->Draw("MiniGame", "white", mXPosMiniGame, mYPosMiniGame);
					mConsole->Draw("Exit", "blue", mXPosExit, mYPosExit);
				}

				mSelectGeneralMenu = GeneralMenu::Exit;
			}

			if (mMouse->XPosClick() > mXPosTypingPracticeHitboxLT && mMouse->XPosClick() < mXPosTypingPracticeHitboxRB && mMouse->YPosClick() > mYPosTypingPracticeHitboxLT && mMouse->YPosClick() < mYPosTypingPracticeHitboxRB)
			{
				mSelectGeneralMenu = GeneralMenu::TypingPractice;
				quit = true;
				break;
			}
			else if (mMouse->XPosClick() > mXPosMiniGameHitboxLT && mMouse->XPosClick() < mXPosMiniGameHitboxRB && mMouse->YPosClick() > mYPosMiniGameHitboxLT && mMouse->YPosClick() < mYPosMiniGameHitboxRB) {
				mSelectGeneralMenu = GeneralMenu::MiniGame;
				quit = true;
				break;
			}
			else if (mMouse->XPosClick() > mXPosExitHitboxLT && mMouse->XPosClick() < mXPosExitHitboxRB && mMouse->YPosClick() > mYPosExitHitboxLT && mMouse->YPosClick() < mYPosExitHitboxRB) {
				mSelectGeneralMenu = GeneralMenu::Exit;
				quit = true;
				break;
			}

		}

		if (quit == true)
			break;



	}
}


//////////////////
/* Phase 2 메뉴 */
//////////////////
void MainMenu::RenderPracticeMenu()
{
	for (bool quit = false;;)
	{
		mConsole->Draw("Assets/layout/mainmenu_practicebox.txt", "white", mXPosPracticeBox, mYPosPracticeBox);
		mConsole->Draw("Word", "white", mXPosWordPractice, mYPosWordPractice);
		mConsole->Draw("Short", "white", mXPosShortPractice, mYPosShortPractice);
		mConsole->Draw("Long", "white", mXPosLongPractice, mYPosLongPractice);
		mConsole->Draw("Statistics", "white", mXPosStatistics, mYPosStatistics);
		mConsole->Draw("Back", "white", mXPosBack, mYPosBack);

		switch (mSelectPracticeMenu)
		{
		case PracticeMenu::Word:
			mConsole->Draw("Word", "red", mXPosWordPractice, mYPosWordPractice);
			break;

		case PracticeMenu::Short:
			mConsole->Draw("Short", "green", mXPosShortPractice, mYPosShortPractice);
			break;

		case PracticeMenu::Long:
			mConsole->Draw("Long", "yellow", mXPosLongPractice, mYPosLongPractice);
			break;

		case PracticeMenu::Statistics:
			mConsole->Draw("Statistics", "purple", mXPosStatistics, mYPosStatistics);
			break;

		case PracticeMenu::Back:
			mConsole->Draw("Back", "blue", mXPosBack, mYPosBack);
			break;
		}

		for (mKeyboard->Clear();;)
		{
			mKeyboard->DynamicInput();               // 화살표 키 또는 엔터 키 대기

			if (mKeyboard->IsPressed("up") || mKeyboard->IsPressed("left"))        // 화살표 위
			{
				mSelectPracticeMenu--;               // 이전 메뉴
				break;
			}

			else if (mKeyboard->IsPressed("down") || mKeyboard->IsPressed("right"))  // 화살표 아래
			{
				mSelectPracticeMenu++;               // 다음 메뉴
				break;
			}

			else if (mKeyboard->IsPressed("enter")) // 엔터
			{
				quit = true;
				break;                              // 반복문 종료
			}

			mMouse->DynamicClick();
			mMouse->DynamicScan();

			if (mMouse->XPosScan() > mXPosWordHitboxLT && mMouse->XPosScan() < mXPosWordHitboxRB && mMouse->YPosScan() > mYPosWordHitboxLT && mMouse->YPosScan() < mYPosWordHitboxRB)
			{
				if (mSelectPracticeMenu != PracticeMenu::Word)
				{
					mConsole->Draw("Word", "red", mXPosWordPractice, mYPosWordPractice);
					mConsole->Draw("Short", "white", mXPosShortPractice, mYPosShortPractice);
					mConsole->Draw("Long", "white", mXPosLongPractice, mYPosLongPractice);
					mConsole->Draw("Statistics", "white", mXPosStatistics, mYPosStatistics);
					mConsole->Draw("Back", "white", mXPosBack, mYPosBack);
				}

				mSelectPracticeMenu = PracticeMenu::Word;
			}

			else if (mMouse->XPosScan() > mXPosShortHitboxLT && mMouse->XPosScan() < mXPosShortHitboxRB && mMouse->YPosScan() > mYPosShortHitboxLT && mMouse->YPosScan() < mYPosShortHitboxRB)
			{
				if (mSelectPracticeMenu != PracticeMenu::Short)
				{
					mConsole->Draw("Word", "white", mXPosWordPractice, mYPosWordPractice);
					mConsole->Draw("Short", "green", mXPosShortPractice, mYPosShortPractice);
					mConsole->Draw("Long", "white", mXPosLongPractice, mYPosLongPractice);
					mConsole->Draw("Statistics", "white", mXPosStatistics, mYPosStatistics);
					mConsole->Draw("Back", "white", mXPosBack, mYPosBack);
				}

				mSelectPracticeMenu = PracticeMenu::Short;
			}

			else if (mMouse->XPosScan() > mXPosLongHitboxLT && mMouse->XPosScan() < mXPosLongHitboxRB && mMouse->YPosScan() > mYPosLongHitboxLT && mMouse->YPosScan() < mYPosLongHitboxRB)
			{
				if (mSelectPracticeMenu != PracticeMenu::Long)
				{
					mConsole->Draw("Word", "white", mXPosWordPractice, mYPosWordPractice);
					mConsole->Draw("Short", "white", mXPosShortPractice, mYPosShortPractice);
					mConsole->Draw("Long", "yellow", mXPosLongPractice, mYPosLongPractice);
					mConsole->Draw("Statistics", "white", mXPosStatistics, mYPosStatistics);
					mConsole->Draw("Back", "white", mXPosBack, mYPosBack);
				}

				mSelectPracticeMenu = PracticeMenu::Long;
			}

			else if (mMouse->XPosScan() > mXPosStatisticsHitboxLT && mMouse->XPosScan() < mXPosStatisticsHitboxRB && mMouse->YPosScan() > mYPosStatisticsHitboxLT && mMouse->YPosScan() < mYPosStatisticsHitboxRB)
			{
				if (mSelectPracticeMenu != PracticeMenu::Statistics)
				{
					mConsole->Draw("Word", "white", mXPosWordPractice, mYPosWordPractice);
					mConsole->Draw("Short", "white", mXPosShortPractice, mYPosShortPractice);
					mConsole->Draw("Long", "white", mXPosLongPractice, mYPosLongPractice);
					mConsole->Draw("Statistics", "purple", mXPosStatistics, mYPosStatistics);
					mConsole->Draw("Back", "white", mXPosBack, mYPosBack);
				}

				mSelectPracticeMenu = PracticeMenu::Statistics;
			}

			else if (mMouse->XPosScan() > mXPosBackHitboxLT && mMouse->XPosScan() < mXPosBackHitboxRB && mMouse->YPosScan() > mYPosBackHitboxLT && mMouse->YPosScan() < mYPosBackHitboxRB)
			{
				if (mSelectPracticeMenu != PracticeMenu::Back)
				{
					mConsole->Draw("Word", "white", mXPosWordPractice, mYPosWordPractice);
					mConsole->Draw("Short", "white", mXPosShortPractice, mYPosShortPractice);
					mConsole->Draw("Long", "white", mXPosLongPractice, mYPosLongPractice);
					mConsole->Draw("Statistics", "white", mXPosStatistics, mYPosStatistics);
					mConsole->Draw("Back", "blue", mXPosBack, mYPosBack);
				}

				mSelectPracticeMenu = PracticeMenu::Back;
			}

			if (mMouse->XPosClick() > mXPosWordHitboxLT && mMouse->XPosClick() < mXPosWordHitboxRB && mMouse->YPosClick() > mYPosWordHitboxLT && mMouse->YPosClick() < mYPosWordHitboxRB)
			{
				mSelectPracticeMenu = PracticeMenu::Word;
				quit = true;
				break;
			}
			else if (mMouse->XPosClick() > mXPosShortHitboxLT && mMouse->XPosClick() < mXPosShortHitboxRB && mMouse->YPosClick() > mYPosShortHitboxLT && mMouse->YPosClick() < mYPosShortHitboxRB) 
			{
				mSelectPracticeMenu = PracticeMenu::Short;
				quit = true;
				break;
			}
			else if (mMouse->XPosClick() > mXPosLongHitboxLT && mMouse->XPosClick() < mXPosLongHitboxRB && mMouse->YPosClick() > mYPosLongHitboxLT && mMouse->YPosClick() < mYPosLongHitboxRB) 
			{
				mSelectPracticeMenu = PracticeMenu::Long;
				quit = true;
				break;
			}
			else if (mMouse->XPosClick() > mXPosStatisticsHitboxLT && mMouse->XPosClick() < mXPosStatisticsHitboxRB && mMouse->YPosClick() > mYPosStatisticsHitboxLT && mMouse->YPosClick() < mYPosStatisticsHitboxRB) 
			{
				mSelectPracticeMenu = PracticeMenu::Statistics;
				quit = true;
				break;
			}
			else if (mMouse->XPosClick() > mXPosBackHitboxLT && mMouse->XPosClick() < mXPosBackHitboxRB && mMouse->YPosClick() > mYPosBackHitboxLT && mMouse->YPosClick() < mYPosBackHitboxRB) 
			{
				mSelectPracticeMenu = PracticeMenu::Back;
				quit = true;
				break;
			}
		}

		if (quit == true)
			break;
	}
}


//////////
/* 메인 */
//////////
void MainMenu::Main()
{
	RenderLayout(); // 레이아웃 출력

	for (mMoveScreen = false; !mMoveScreen;)    // 사용자가 기능을 요청할 때까지 반복
	{
		mConsole->Clear(mXPosMenuBox, mYPosMenuBox, mWidthMenuBox, mHeightMenuBox);     // 메뉴 상자를 비움
		RenderGeneralMenu();                                                            // Phase 1 실행

		switch (mSelectGeneralMenu)                                                     // Phase 1의 결과 확인
		{
		case GeneralMenu::TypingPractice:                                               // 타자 연습이라면
			mConsole->Clear(mXPosMenuBox, mYPosMenuBox, mWidthMenuBox, mHeightMenuBox); // 메뉴 상자를 비우고
			RenderPracticeMenu();                                                       // Phase 2 실행

			switch (mSelectPracticeMenu)            // Phase 2의 결과 확인
			{
			case PracticeMenu::Word:                // 단어연습
				mNextScreen = Screen::WordPractice; // 다음으로 실행할 기능 업데이트
				mMoveScreen = true;                 // 화면 이동 필요
				break;

			case PracticeMenu::Short:               // 짧은 글 연습
				mNextScreen = Screen::ShortPractice;
				mMoveScreen = true;
				break;

			case PracticeMenu::Long:                // 긴 글 연습
				mNextScreen = Screen::LongPractice;
				mMoveScreen = true;
				break;

			case PracticeMenu::Statistics:          // 통계
				mNextScreen = Screen::Statistics;
				mMoveScreen = true;
				break;

			case PracticeMenu::Back:                // Phase 1로 이동
				mNextScreen = Screen::WordPractice;
				break;
			}
			break;

		case GeneralMenu::MiniGame:         // 미니 게임
			mNextScreen = Screen::MiniGame;
			mMoveScreen = true;
			break;

		case GeneralMenu::Exit:             // 프로그램 종료
			mNextScreen = Screen::Exit;
			mMoveScreen = true;
			break;
		}
	}

	mKeyboard->Clear();
	mConsole->Clear();
	mConsole->Color("default");
}


////////////////////
/* 다음 기능 반환 */
////////////////////
Screen MainMenu::NextScreen()
{
	return mNextScreen;
}


MainMenu* MainMenu::sInstance = nullptr;

MainMenu* MainMenu::Instance()
{
	if (sInstance == nullptr)
		sInstance = new MainMenu;

	return sInstance;
}

void MainMenu::Release()
{
	delete sInstance;
	sInstance = nullptr;
}
