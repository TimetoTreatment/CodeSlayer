#include "ShortPractice.h"


ShortPractice::ShortPractice()
{

}


ShortPractice::~ShortPractice()
{

}


///////////////
/* ���� ȭ�� */
///////////////
void ShortPractice::RenderIntro()
{
	mConsole->Draw("Assets/layout/practice_intro.txt", "white", 19, 7);
	mConsole->Draw("Typing Practice", "white", mXPosTitleStart + 2, mYPosTitleStart);
	mConsole->Draw("Short", "green", mXPosTitleStart + 7, mYPosTitleStart + 2);

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
}


void ShortPractice::RenderPractice()
{
	string presetCode;	// ������ �ڵ�
	string userCode;	// ����� �ڵ�
	int currentWord;
	int testPageNum = (mTestCase - 1) / 5 + 1;

	mTimer->Reset();
	mKeyboard->Clear();
	mConsole->Clear();
	mConsole->Draw("Assets/layout/practice_main.txt", "white", 0, 1);

	mPresetTotalCh = 0;	// ������ ���� ��
	mUserTotalCh = 0;	// ����� ���� ��
	mUserWrongCh = 0;	// ��Ÿ ���� ��

	for (int testPageCount = 0; testPageCount < testPageNum; testPageCount++)
	{
		for (currentWord = 0; currentWord < 5 && testPageCount * 5 + currentWord < mTestCase; currentWord++)
		{
			presetCode = GetRandomText("short").GetText();

			mConsole->Draw(presetCode, "yellow", mXPosPresetCodeStart, mYPosPresetCodeStart + currentWord * 3);	// ���� �Է��ؾ� �ϴ� �ܾ ��������� ����

			mConsole->Color("white");																// �ܼ� �ؽ�Ʈ ���� ����
			mConsole->CursorPosition(mXPosUserCodeStart, mYPosUserCodeStart + currentWord * 3);		// ����� �Է� ��ġ�� Ŀ�� �̵�

			getline(cin, userCode);					// �� �� �б�

			mPresetTotalCh += presetCode.size();	// ������ ���� �� ������Ʈ
			mUserTotalCh += userCode.size();		// ����� ���� �� ������Ʈ

			mTypingSpeed = (int)(mUserTotalCh / mTimer->GetElapsedTime() * 60);		// �ӵ� ������Ʈ

			if (presetCode == userCode)																			// ����
			{
				mConsole->Draw(userCode, "green", mXPosUserCodeStart, mYPosUserCodeStart + currentWord * 3);	// �ʷϻ����� ����
				mConsole->Draw("Good", "green", mXPosCurrect, mYPosCurrect);									// ���� �޽��� ���
			}
			else															// ����
			{
				for (size_t count = 0; count < presetCode.size(); count++)	// ����� ��Ÿ ���� �� ������Ʈ
				{
					if (count < userCode.size())							// ����� �ڵ� ���� �̳�����
					{
						if (userCode[count] != presetCode[count])			// Ʋ�ȴٸ�
							mUserWrongCh++;									// ��Ÿ ���� �� ����
					}
					else													// ����� �ڵ� ���� �̿ܶ��
						mUserWrongCh++;										// ��Ÿ ���� �� ����
				}

				mConsole->Draw(userCode, "red", mXPosUserCodeStart, mYPosUserCodeStart + currentWord * 3);
				mConsole->Draw("Bad ", "red", mXPosCurrect, mYPosCurrect);	// ���������� ����, ���� �޽��� ���
			}

			mTypingAccuracy = 100 - mUserWrongCh * 100 / mPresetTotalCh;	// ��Ȯ�� ������Ʈ

			mConsole->Clear(mXPosSpeed, mYPosSpeed, 4, 1);														// �ӵ� ���� ����
			mConsole->Clear(mXPosAccuracy, mYPosAccuracy, 4, 1);												// ��Ȯ�� ���� ����
			mConsole->Draw(to_string(mTypingSpeed), "white", mXPosSpeed, mYPosSpeed);							// �ӵ� ���
			mConsole->Draw(to_string(mTypingAccuracy), "white", mXPosAccuracy, mYPosAccuracy);					// ��Ȯ�� ���
			mConsole->Draw(presetCode, "white", mXPosPresetCodeStart, mYPosPresetCodeStart + currentWord * 3);	// ���� ������ �ܾ ��� ������ �� ������ ���� 
		}

		mConsole->Clear(mXPosPresetCodeStart, mYPosPresetCodeStart, mWidthCodeBox, mHeightCodeBox);	// ������ �ڵ�(�ܾ�) ���� ����
		mConsole->Clear(mXPosUserCodeStart, mYPosUserCodeStart, mWidthCodeBox, mHeightCodeBox);		// ���� �ڵ�(�ܾ�) ���� ����
	}

	mConsole->Clear();
	mKeyboard->Clear();
}


///////////////
/* ���� ȭ�� */
///////////////
void ShortPractice::RenderResult()
{
	mConsole->Clear();
	mKeyboard->Clear();

	mConsole->Draw("Assets/layout/practice_intro.txt", "white", 19, 7);
	mConsole->Draw("Speed : ", "white", mXPosTitleStart + 3, mYPosTitleStart);
	mConsole->CursorPosition(mXPosTitleStart + 11, mYPosTitleStart);

	if (mTypingSpeed >= mRecentSpeed.back())	// ������ ��Ϻ��� �������ٸ�
		mConsole->Color("green");				// ���� �ؽ�Ʈ�� �ʷϻ����� ����
	else mConsole->Color("red");				// �������ٸ� ���������� ����

	cout << mTypingSpeed;						// �ӵ� ���
	mConsole->Color("white");
	cout << " / min";

	mConsole->Draw("Accuracy : ", "white", mXPosTitleStart, mYPosTitleStart + 2);
	mConsole->CursorPosition(mXPosTitleStart + 11, mYPosTitleStart + 2);

	if (mTypingAccuracy >= mRecentAccuracy.back())
		mConsole->Color("green");
	else mConsole->Color("red");

	cout << mTypingAccuracy;
	mConsole->Color("white");
	cout << " %";

	for (;;)	// ���� ������Ʈ
	{
		mConsole->Draw("* Press Enter to Quit *", "white", mXPosPrompt, mYPosPrompt);	// ���� ������Ʈ
		mConsole->Draw("y", "random", mXPosTrafficLight, mYPosTrafficLight);			// ���� 1
		mConsole->Draw("y", "random", mXPosTrafficLight + 6, mYPosTrafficLight);		// ���� 2
		mConsole->Draw("y", "random", mXPosTrafficLight + 12, mYPosTrafficLight);		// ���� 3
		Sleep(250);

		mKeyboard->DynamicInput();			// ���� �Է�
		if (mKeyboard->IsPressed("enter"))	// ���Ͱ� �ԷµǾ��ٸ�
			break;							// �ݺ��� ����

		mConsole->Draw("* Press Enter to Quit *", "yellow", mXPosPrompt, mYPosPrompt);
		mConsole->Draw("y", "random", mXPosTrafficLight, mYPosTrafficLight);
		mConsole->Draw("y", "random", mXPosTrafficLight + 6, mYPosTrafficLight);
		mConsole->Draw("y", "random", mXPosTrafficLight + 12, mYPosTrafficLight);
		Sleep(250);

		mKeyboard->DynamicInput();
		if (mKeyboard->IsPressed("enter"))
			break;
	}

	mConsole->Clear();
	mKeyboard->Clear();
}


////////////////////
/* ��� ���� �б� */
////////////////////
void ShortPractice::ReadResultFile()
{
	string numStr;
	fstream fileAccuracy("Assets/statistics/shortaccuracy.txt", ios::in);
	fstream fileSpeed("Assets/statistics/shortspeed.txt", ios::in);

	if (fileAccuracy.fail() || fileSpeed.fail())
	{
		cout << "ERROR : ShortPractice::ReadResultFIle()\n";
		exit(-1);
	}

	for (mRecentResultNum = 0; fileAccuracy >> numStr; mRecentResultNum++)
	{
		mRecentAccuracy.push(stoi(numStr));	// ��Ȯ���� ť�� �߰�
		fileSpeed >> numStr;
		mRecentSpeed.push(stoi(numStr));	// �ӵ��� ť�� �߰�
	}

	fileAccuracy.close();
	fileSpeed.close();
}


////////////////////
/* ��� ���� ���� */
////////////////////
void ShortPractice::WriteResultFile()
{
	fstream fileAccuracy("Assets/statistics/shortaccuracy.txt", ios::out);
	fstream fileSpeed("Assets/statistics/shortspeed.txt", ios::out);

	if (fileAccuracy.fail() || fileSpeed.fail())
	{
		cout << "ERROR : ShortPractice::WriteResultFIle()\n";
		exit(-1);
	}

	if (mRecentResultNum == 5)	// ť�� 5���� ����� �ִٸ�
	{
		mRecentAccuracy.pop();	// ��Ȯ�� �� �� ����
		mRecentSpeed.pop();		// �ӵ� �� �� ����
	}

	mRecentAccuracy.push(mTypingAccuracy);	// ���� ��Ȯ���� ť�� ����
	mRecentSpeed.push(mTypingSpeed);		// ���� �ӵ��� ť�� ����

	for (; mRecentAccuracy.size() > 1;)
	{
		fileAccuracy << mRecentAccuracy.front() << ' ';		// ���ʴ�� ���, �������� ����
		fileSpeed << mRecentSpeed.front() << ' ';			//

		mRecentAccuracy.pop();	// ��� �� ����
		mRecentSpeed.pop();		//
	}

	fileAccuracy << mRecentAccuracy.front();
	fileSpeed << mRecentSpeed.front();

	mRecentAccuracy.pop();
	mRecentSpeed.pop();

	fileAccuracy.close();
	fileSpeed.close();
}


void ShortPractice::Main()
{
	ReadResultFile();	// ��� ���� �б�

	RenderIntro();		// ���� ȭ��
	RenderPractice();	// Ÿ�� ����
	RenderResult();		// ��� ȭ��

	WriteResultFile();	// ��� ���� ����
}


ShortPractice* ShortPractice::sInstance = nullptr;

ShortPractice* ShortPractice::Instance() 
{
	if (sInstance == nullptr)
		sInstance = new ShortPractice;

	return sInstance;
}

void ShortPractice::Release()
{
	delete sInstance;
	sInstance = nullptr;
}