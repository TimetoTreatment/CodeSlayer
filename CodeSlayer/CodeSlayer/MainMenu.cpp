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
	bool quit = false;

	for (;;)
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


		quit = false;

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

			mMouse->dynamic();

			if (mMouse->GetX() > mXPosTypingPracticeHitboxLT && mMouse->GetX() < mXPosTypingPracticeHitboxRB && mMouse->GetY() > mYPosTypingPracticeHitboxLT && mMouse->GetY() < mYPosTypingPracticeHitboxRB)
			{
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
	for (;;)
	{
		mConsole->Draw("Assets/layout/mainmenu_practicebox.txt", "white", mXPosPracticeBox, mYPosPracticeBox);
		mConsole->Draw("Word", "white", mXPosWordPractice, mYPosWordPractice);
		mConsole->Draw("Short", "white", mXPosShortPractice, mYPosShortPractice);
		mConsole->Draw("Long", "white", mXPosLongPractice, mYPosLongPractice);
		mConsole->Draw("Statistics", "white", mXPosStatisticsPractice, mYPosStatisticsPractice);
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
			mConsole->Draw("Statistics", "purple", mXPosStatisticsPractice, mYPosStatisticsPractice);
			break;

		case PracticeMenu::Back:
			mConsole->Draw("Back", "blue", mXPosBack, mYPosBack);
			break;
		}

		mKeyboard->StaticInput();

		if (mKeyboard->IsPressed("up") || mKeyboard->IsPressed("left"))
			mSelectPracticeMenu--;

		else if (mKeyboard->IsPressed("down") || mKeyboard->IsPressed("right"))
			mSelectPracticeMenu++;

		else if (mKeyboard->IsPressed("enter"))
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