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
/* ���̾ƿ� ��� */
///////////////////
void MainMenu::RenderLayout()
{
	mConsole->Draw("Assets/layout/intro_programLogo.txt", "blue", 10, 5);   // ���α׷� �ΰ�
	mConsole->Draw("Assets/layout/mainmenu_brickwall.txt", "white", 6, 17); // ���� ��
}


//////////////////
/* Phase 2 �޴� */
//////////////////
void MainMenu::RenderGeneralMenu()
{
    for (bool quit = false;;)
    {
        /* ��� �׸��� ������� ��� */
        mConsole->Draw("Typing Practice", "white", mXPosTypingPractice, mYPosTypingPractice);
        mConsole->Draw("MiniGame", "white", mXPosMiniGame, mYPosMiniGame);
        mConsole->Draw("Exit", "white", mXPosExit, mYPosExit);

        switch (mSelectGeneralMenu)                                                             // ���� ������ �޴�   
        {
        case GeneralMenu::TypingPractice:                                                       // Ÿ�� ����
            mConsole->Draw("Typing Practice", "red", mXPosTypingPractice, mYPosTypingPractice); // ���� ����
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
            mKeyboard->DynamicInput();               // ȭ��ǥ Ű �Ǵ� ���� Ű ���

            if (mKeyboard->IsPressed("up"))         // ȭ��ǥ ��
            {
                mSelectGeneralMenu--;               // ���� �޴�
                break;
            }

            else if (mKeyboard->IsPressed("down"))  // ȭ��ǥ �Ʒ�
            {
                mSelectGeneralMenu++;               // ���� �޴�
                break;
            }

            else if (mKeyboard->IsPressed("enter")) // ����
            {
                quit = true;
                break;                              // �ݺ��� ����
            }

            mMouse->DynamicClick();

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
/* Phase 2 �޴� */
//////////////////
void MainMenu::RenderPracticeMenu()
{
    for (bool quit = false;;)
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

        for (mKeyboard->Clear();;)
        {
            mKeyboard->DynamicInput();               // ȭ��ǥ Ű �Ǵ� ���� Ű ���

            if (mKeyboard->IsPressed("up") || mKeyboard->IsPressed("left"))        // ȭ��ǥ ��
            {
                mSelectPracticeMenu--;               // ���� �޴�
                break;
            }

            else if (mKeyboard->IsPressed("down") || mKeyboard->IsPressed("right"))  // ȭ��ǥ �Ʒ�
            {
                mSelectPracticeMenu++;               // ���� �޴�
                break;
            }

            else if (mKeyboard->IsPressed("enter")) // ����
            {
                quit = true;
                break;                              // �ݺ��� ����
            }

            mMouse->DynamicClick();
            mMouse->DynamicScan();

            if (mMouse->XPosScan() > mXPosWordHitboxLT && mMouse->XPosScan() < mXPosWordHitboxRB && mMouse->YPosScan() > mYPosWordHitboxLT && mMouse->YPosScan() < mYPosWordHitboxRB)
            {
                if (mSelectPracticeMenu != PracticeMenu::Word)
                {
                    mConsole->Draw("Short", "white", mXPosShortPractice, mYPosShortPractice);
                    mConsole->Draw("Long", "white", mXPosLongPractice, mYPosLongPractice);
                    mConsole->Draw("Statistics", "white", mXPosStatisticsPractice, mYPosStatisticsPractice);
                    mConsole->Draw("Back", "white", mXPosBack, mYPosBack);

                    mConsole->Draw("Word", "red", mXPosWordPractice, mYPosWordPractice);
                }

                mSelectPracticeMenu = PracticeMenu::Word;
            }

            if (mMouse->XPosClick() > mXPosWordHitboxLT && mMouse->XPosClick() < mXPosWordHitboxRB && mMouse->YPosClick() > mYPosWordHitboxLT && mMouse->YPosClick() < mYPosWordHitboxRB)
            {
                mSelectPracticeMenu = PracticeMenu::Word;
                quit = true;
                break;
            }
            else if (mMouse->XPosClick() > mXPosShortHitboxLT && mMouse->XPosClick() < mXPosShortHitboxRB && mMouse->YPosClick() > mYPosShortHitboxLT && mMouse->YPosClick() < mYPosShortHitboxRB) {
                mSelectPracticeMenu = PracticeMenu::Short;
                quit = true;
                break;
            }
            else if (mMouse->XPosClick() > mXPosLongHitboxLT && mMouse->XPosClick() < mXPosLongHitboxRB && mMouse->YPosClick() > mYPosLongHitboxLT && mMouse->YPosClick() < mYPosLongHitboxRB) {
                mSelectPracticeMenu = PracticeMenu::Long;
                quit = true;
                break;
            }
            else if (mMouse->XPosClick() > mXPosStatisticsHitboxLT && mMouse->XPosClick() < mXPosStatisticsHitboxRB && mMouse->YPosClick() > mYPosStatisticsHitboxLT && mMouse->YPosClick() < mYPosStatisticsHitboxRB) {
                mSelectPracticeMenu = PracticeMenu::Statistics;
                quit = true;
                break;
            }
            else if (mMouse->XPosClick() > mXPosBackHitboxLT && mMouse->XPosClick() < mXPosBackHitboxRB && mMouse->YPosClick() > mYPosBackHitboxLT && mMouse->YPosClick() < mYPosBackHitboxRB) {
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
/* ���� */
//////////
void MainMenu::Main()
{
	RenderLayout(); // ���̾ƿ� ���

	for (mMoveScreen = false; !mMoveScreen;)    // ����ڰ� ����� ��û�� ������ �ݺ�
	{
		mConsole->Clear(mXPosMenuBox, mYPosMenuBox, mWidthMenuBox, mHeightMenuBox);     // �޴� ���ڸ� ���
		RenderGeneralMenu();                                                            // Phase 1 ����

		switch (mSelectGeneralMenu)                                                     // Phase 1�� ��� Ȯ��
		{
		case GeneralMenu::TypingPractice:                                               // Ÿ�� �����̶��
			mConsole->Clear(mXPosMenuBox, mYPosMenuBox, mWidthMenuBox, mHeightMenuBox); // �޴� ���ڸ� ����
			RenderPracticeMenu();                                                       // Phase 2 ����

			switch (mSelectPracticeMenu)            // Phase 2�� ��� Ȯ��
			{
			case PracticeMenu::Word:                // �ܾ��
				mNextScreen = Screen::WordPractice; // �������� ������ ��� ������Ʈ
				mMoveScreen = true;                 // ȭ�� �̵� �ʿ�
				break;

			case PracticeMenu::Short:               // ª�� �� ����
				mNextScreen = Screen::ShortPractice;
				mMoveScreen = true;
				break;

			case PracticeMenu::Long:                // �� �� ����
				mNextScreen = Screen::LongPractice;
				mMoveScreen = true;
				break;

			case PracticeMenu::Statistics:          // ���
				mNextScreen = Screen::Statistics;
				mMoveScreen = true;
				break;

			case PracticeMenu::Back:                // Phase 1�� �̵�
				mNextScreen = Screen::WordPractice;
				break;
			}
			break;

		case GeneralMenu::MiniGame:         // �̴� ����
			mNextScreen = Screen::MiniGame;
			mMoveScreen = true;
			break;

		case GeneralMenu::Exit:             // ���α׷� ����
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
/* ���� ��� ��ȯ */
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