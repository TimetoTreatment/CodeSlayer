#include "LongPractice.h"


LongPractice::LongPractice()
{

}


LongPractice::~LongPractice()
{

}


///////////////
/* ���� ȭ�� */
///////////////
void LongPractice::RenderIntro()
{
	mConsole->Draw("Assets/layout/practice_intro.txt", "white", 19, 7);
	mConsole->Draw("Typing Practice", "white", mXPosTitleStart + 2, mYPosTitleStart);
	mConsole->Draw("Long", "yellow", mXPosTitleStart + 7, mYPosTitleStart + 2);

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


///////////////
/* Ÿ�� ���� */
///////////////
void LongPractice::RenderPractice()
{
	string presetCode;			// ��ü ������ �ڵ�
	string presetLine;			// ������ ���� 
	string presetLineOrganized;	// ������ ���� �ڵ�ȭ
	string userLine;			// ���� �Է� ����
	string userLineOrganized;	// ���� �Է� ���� �ڵ�ȭ
	size_t indentation;			// �鿩����
	size_t CurrentIndentation;	// ���� �鿩���� ��
	size_t prePos, pos;
	size_t currentLine;

	mTimer->Reset();
	mKeyboard->Clear();
	mConsole->Clear();
	mConsole->Draw("Assets/layout/practice_main.txt", "white", 0, 1);

	mPresetTotalCh = 0;	// ������ ���� ��
	mUserTotalCh = 0;	// ����� ���� ��
	mUserWrongCh = 0;	// ��Ÿ ���� ��

	for (int testNum = 0; testNum < mTestCase; testNum++)
	{
		presetCode = GetRandomText("long").GetText();										// ������ ������ �ڵ�� ����

		mConsole->Draw(presetCode, "white", mXPosPresetCodeStart, mYPosPresetCodeStart);	// ������ �ڵ� ���

		pos = 0;
		prePos = 0;

		for (currentLine = 0; (pos = presetCode.find('\n', pos + 1)) < presetCode.size(); currentLine++)
		{
			presetLine = presetCode.substr(prePos, pos - prePos);											// �������� �� �� ����
			mConsole->Draw(presetLine, "yellow", mXPosPresetCodeStart, mYPosPresetCodeStart + currentLine);	// ���� �Է��ؾ� �ϴ� ���̹Ƿ�, ��������� ���
			prePos = pos + 1;

			indentation = Whitespace(presetLine);	// �鿩���� ���
			presetLineOrganized = presetLine;		// ������ �ڵ� ���� ����
			OrganizeCode(presetLineOrganized);		// ������ �ڵ� ���� ����

			mConsole->Color("white");																// �ܼ� �ؽ�Ʈ ���� ����
			mConsole->CursorPosition(mXPosUserCodeStart, mYPosUserCodeStart + currentLine);			// ����� �Է� ��ġ�� Ŀ�� �̵�

			for (CurrentIndentation = 0; CurrentIndentation < indentation; CurrentIndentation++)	// �鿩���� ��ĭ ����
				cout << " ";

			getline(cin, userLine);				// ����ڷκ��� �� �� �б�

			userLineOrganized = userLine;		// ����� �ڵ� ���� ����
			OrganizeCode(userLineOrganized);	// ����� �ڵ� ���� ����

			mPresetTotalCh += presetLineOrganized.size();						// ������ ���� �� ������Ʈ
			mUserTotalCh += userLineOrganized.size();							// ����� ���� �� ������Ʈ
			mTypingSpeed = (int)(mUserTotalCh / mTimer->GetElapsedTime() * 60);	// �ӵ� ������Ʈ

			if (presetLineOrganized == userLineOrganized)																// ����
			{
				mConsole->Draw(userLine, "green", mXPosUserCodeStart + indentation, mYPosUserCodeStart + currentLine);	// �ʷϻ����� ����
				mConsole->Draw("Good", "green", mXPosCurrect, mYPosCurrect);											// ���� �޽��� ���
			}
			else																	// ����
			{
				for (size_t count = 0; count < presetLineOrganized.size(); count++)	// ����� ��Ÿ ���� �� ������Ʈ
				{
					if (count < userLine.size())									// ����� �ڵ� ���� �̳�����
					{
						if (userLine[count] != presetLineOrganized[count])			// Ʋ�ȴٸ�
							mUserWrongCh++;											// ��Ÿ ���� �� ����
					}
					else															// ����� �ڵ� ���� �̿ܶ��
						mUserWrongCh++;												// ��Ÿ ���� �� ����
				}

				mConsole->Draw(userLine, "red", mXPosUserCodeStart + indentation, mYPosUserCodeStart + currentLine);
				mConsole->Draw("Bad ", "red", mXPosCurrect, mYPosCurrect);			// ���������� ����, ���� �޽��� ���
			}

			mTypingAccuracy = 100 - mUserWrongCh * 100 / mPresetTotalCh;						// ��Ȯ�� ������Ʈ

			mConsole->Clear(mXPosSpeed, mYPosSpeed, 4, 1);										// �ӵ� ���� ����
			mConsole->Clear(mXPosAccuracy, mYPosAccuracy, 4, 1);								// ��Ȯ�� ���� ����
			mConsole->Draw(to_string(mTypingSpeed), "white", mXPosSpeed, mYPosSpeed);			// �ӵ� ���
			mConsole->Draw(to_string(mTypingAccuracy), "white", mXPosAccuracy, mYPosAccuracy);	// ��Ȯ�� ���
			mConsole->Draw(presetLine, "white", mXPosPresetCodeStart, mYPosPresetCodeStart + currentLine);	// ���� ������ ������ ��� ������ �� ������ ����
		}

		mConsole->Clear(mXPosPresetCodeStart, mYPosPresetCodeStart, mWidthCodeBox, mHeightCodeBox);	// ������ �ڵ� ���� ����
		mConsole->Clear(mXPosUserCodeStart, mYPosUserCodeStart, mWidthCodeBox, mHeightCodeBox);		// ����� �ڵ� ���� ����
	}

	mConsole->Clear();	// �ܼ� ȭ�� ����
	mKeyboard->Clear();	// Ű���� �Է� �ʱ�ȭ
}


///////////////
/* ���� ȭ�� */
///////////////
void LongPractice::RenderResult()
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
void LongPractice::ReadResultFile()
{
	string numStr;
	fstream fileAccuracy("Assets/statistics/longaccuracy.txt", ios::in);
	fstream fileSpeed("Assets/statistics/longspeed.txt", ios::in);

	if (!fileAccuracy.good() || !fileSpeed.good())
	{
		cout << "ERROR : LongPractice::ReadResultFIle()\n";
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
void LongPractice::WriteResultFile()
{
	fstream fileAccuracy("Assets/statistics/longaccuracy.txt", ios::out);
	fstream fileSpeed("Assets/statistics/longspeed.txt", ios::out);

	if (!fileAccuracy.good() || !fileSpeed.good())
	{
		cout << "ERROR : LongPractice::WriteResultFIle()\n";
		exit(-1);
	}

	if (mRecentResultNum == 5)	// ť�� 5���� ����� �ִٸ�
	{
		mRecentAccuracy.pop();	// ��Ȯ�� �� �� ����
		mRecentSpeed.pop();		// �ӵ� �� �� ����
	}

	mRecentAccuracy.push(mTypingAccuracy);	// ���� ��Ȯ���� ť�� ����
	mRecentSpeed.push(mTypingSpeed);		// ���� �ӵ��� ť�� ����

	/* ť�� ��Ȯ���� �ӵ��� ���Ͽ� ��� */
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


////////////////////////
/* �鿩���� ��ĭ ��� */
////////////////////////
size_t LongPractice::Whitespace(const string& currentLine) const
{
	size_t indentation;

	for (indentation = 0; indentation < currentLine.size(); indentation++)
	{
		if (currentLine[indentation] != ' ' && currentLine[indentation] != '\t')
			break;
	}

	return indentation;
}


///////////////
/* �ڵ� ���� */
///////////////
void LongPractice::OrganizeCode(string& currentLine)
{
	size_t i;

	/* �鿩���� ��� */
	for (i = 0; i < currentLine.size(); i++)
	{
		if (currentLine[i] != ' ' && currentLine[i] != '\t')
			break;
	}

	currentLine.erase(0, i);	// �鿩���� ����

	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//	
	//        * �⺻ ���� *        //	
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
	/*                              *
		1. ������ �Ǵ� ��ȣ �Ǻ�
		2. �յ� ĭ�� ���� ����
	*                               */

	for (i = 0; i < currentLine.size(); i++)
	{
		if (currentLine[i] == ' ')
		{
			if (i > 0 && IsOperator(currentLine[i - 1]))
			{
				currentLine.erase(i, 1);
				i--;
			}

			else if (i < currentLine.size() - 1 && IsOperator(currentLine[i + 1]))
			{
				currentLine.erase(i, 1);
				i--;
			}
		}
		else if (currentLine[i] == '\t')
		{
			currentLine.erase(i, 1);
			i--;
		}
	}
}


/////////////////
/* ������ �Ǻ� */
/////////////////
bool LongPractice::IsOperator(char ch) const
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=')
		return true;

	if (ch == '&' || ch == '|' || ch == '!' || ch == '>' || ch == '<')
		return true;

	if (ch == '%' || ch == ',' || ch == ';')
		return true;

	if (ch == '(' || ch == '{' || ch == ')' || ch == '}')
		return true;

	return false;
}


//////////
/* ���� */
//////////
void LongPractice::Main()
{
	ReadResultFile();	// ��� ���� �б�

	RenderIntro();		// ���� ȭ��
	RenderPractice();	// Ÿ�� ����
	RenderResult();		// ��� ȭ��

	WriteResultFile();	// ��� ���� ����
}


LongPractice* LongPractice::sInstance = nullptr;

LongPractice* LongPractice::Instance()
{
	if (sInstance == nullptr)
		sInstance = new LongPractice;

	return sInstance;
}

void LongPractice::Release()
{
	delete sInstance;
	sInstance = nullptr;
}