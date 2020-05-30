#include "MainMenu.h"

void operator++(MainMenu::GeneralMenu& lhs, int)
{
	switch (lhs)
	{
	case MainMenu::GeneralMenu::TypingPractice:	lhs = MainMenu::GeneralMenu::MiniGame;			break;
	case MainMenu::GeneralMenu::MiniGame:		lhs = MainMenu::GeneralMenu::Exit;				break;
	case MainMenu::GeneralMenu::Exit:			lhs = MainMenu::GeneralMenu::TypingPractice;	break;
	}
}

void operator--(MainMenu::GeneralMenu& lhs, int)
{
	switch (lhs)
	{
	case MainMenu::GeneralMenu::TypingPractice:	lhs = MainMenu::GeneralMenu::Exit;				break;
	case MainMenu::GeneralMenu::MiniGame:		lhs = MainMenu::GeneralMenu::TypingPractice;	break;
	case MainMenu::GeneralMenu::Exit:			lhs = MainMenu::GeneralMenu::MiniGame;			break;
	}
}

void operator++(MainMenu::PracticeMenu& lhs, int)
{
	switch (lhs)
	{
	case MainMenu::PracticeMenu::Word:		lhs = MainMenu::PracticeMenu::Short;	break;
	case MainMenu::PracticeMenu::Short:		lhs = MainMenu::PracticeMenu::Long;		break;
	case MainMenu::PracticeMenu::Long:		lhs = MainMenu::PracticeMenu::Back;		break;
	case MainMenu::PracticeMenu::Back:		lhs = MainMenu::PracticeMenu::Word;		break;
	}
}

void operator--(MainMenu::PracticeMenu& lhs, int)
{
	switch (lhs)
	{
	case MainMenu::PracticeMenu::Word:		lhs = MainMenu::PracticeMenu::Back;		break;
	case MainMenu::PracticeMenu::Short:		lhs = MainMenu::PracticeMenu::Word;		break;
	case MainMenu::PracticeMenu::Long:		lhs = MainMenu::PracticeMenu::Short;	break;
	case MainMenu::PracticeMenu::Back:		lhs = MainMenu::PracticeMenu::Long;		break;
	}
}


MainMenu::MainMenu()
{
	mConsole = Console::Instance();
	mKeyboard = Keyboard::Instance();

	mSelectGeneralMenu = GeneralMenu::TypingPractice;
	mSelectPracticeMenu = PracticeMenu::Word;

	mNextScreen = Screen::MainMenu;
	mMoveScreen = false;
}


MainMenu::~MainMenu()
{

}


void MainMenu::RenderLayout()
{
	mConsole->Draw("Assets/layout/intro_programLogo.txt", "blue", 10, 5);
	mConsole->Draw("Assets/layout/mainmenu_brickwall.txt", "white", 6, 17);
}


void MainMenu::RenderGeneralMenu()
{
	for (;;)
	{
		mConsole->Draw("Typing Practice", "white", mXPosTypingPractice, mYPosTypingPractice);
		mConsole->Draw("MiniGame", "white", mXPosMiniGame, mYPosMiniGame);
		mConsole->Draw("Exit", "white", mXPosExit, mYPosExit);

		switch (mSelectGeneralMenu)
		{
		case GeneralMenu::TypingPractice:
			mConsole->Draw("Typing Practice", "red", mXPosTypingPractice, mYPosTypingPractice);

			break;

		case GeneralMenu::MiniGame:
			mConsole->Draw("MiniGame", "green", mXPosMiniGame, mYPosMiniGame);

			break;

		case GeneralMenu::Exit:
			mConsole->Draw("Exit", "blue", mXPosExit, mYPosExit);

			break;
		}

		mKeyboard->StaticInput();

		if (mKeyboard->IsPressed("up"))
			mSelectGeneralMenu--;

		else if (mKeyboard->IsPressed("down"))
			mSelectGeneralMenu++;

		else if (mKeyboard->IsPressed("enter"))
			break;
	}
}


void MainMenu::RenderPracticeMenu()
{
	for (;;)
	{
		mConsole->Draw("Word Practice", "white", mXPosWordPractice, mYPosWordPractice);
		mConsole->Draw("Short Practice", "white", mXPosShortPractice, mYPosShortPractice);
		mConsole->Draw("Long Practice", "white", mXPosLongPractice, mYPosLongPractice);
		mConsole->Draw("Back", "white", mXPosBack, mYPosBack);

		switch (mSelectPracticeMenu)
		{
		case PracticeMenu::Word:
			mConsole->Draw("Word Practice", "red", mXPosWordPractice, mYPosWordPractice);
			break;

		case PracticeMenu::Short:
			mConsole->Draw("Short Practice", "green", mXPosShortPractice, mYPosShortPractice);
			break;

		case PracticeMenu::Long:
			mConsole->Draw("Long Practice", "yellow", mXPosLongPractice, mYPosLongPractice);
			break;

		case PracticeMenu::Back:
			mConsole->Draw("Back", "blue", mXPosBack, mYPosBack);
			break;
		}

		mKeyboard->StaticInput();

		if (mKeyboard->IsPressed("up"))
			mSelectPracticeMenu--;

		else if (mKeyboard->IsPressed("down"))
			mSelectPracticeMenu++;

		else if (mKeyboard->IsPressed("enter"))
			break;
	}
}


void MainMenu::Main()
{
	RenderLayout();

	for (mMoveScreen = false; !mMoveScreen;)
	{
		mConsole->Clear(mXPosMenuBox, mYPosMenuBox, mWidthMenuBox, mHeightMenuBox);
		RenderGeneralMenu();

		switch (mSelectGeneralMenu)
		{
		case GeneralMenu::TypingPractice:
			mConsole->Clear(mXPosMenuBox, mYPosMenuBox, mWidthMenuBox, mHeightMenuBox);
			RenderPracticeMenu();

			switch (mSelectPracticeMenu)
			{
			case PracticeMenu::Word:
				mNextScreen = Screen::WordPractice;
				mMoveScreen = true;
				break;

			case PracticeMenu::Short:
				mNextScreen = Screen::ShortPractice;
				mMoveScreen = true;
				break;

			case PracticeMenu::Long:
				mNextScreen = Screen::LongPractice;
				mMoveScreen = true;
				break;

			case PracticeMenu::Back:
				mNextScreen = Screen::WordPractice;
				break;
			}
			break;

		case GeneralMenu::MiniGame:

			mNextScreen = Screen::MiniGame;
			mMoveScreen = true;
			break;

		case GeneralMenu::Exit:
			mNextScreen = Screen::Exit;
			mMoveScreen = true;
			break;
		}
	}

	mKeyboard->Clear();
	mConsole->Clear();
	mConsole->Color("default");
}


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
