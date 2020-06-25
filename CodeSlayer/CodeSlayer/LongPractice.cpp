#include "LongPractice.h"


LongPractice::LongPractice()
{

}


LongPractice::~LongPractice()
{

}


///////////////
/* 시작 화면 */
///////////////
void LongPractice::RenderIntro()
{
	mConsole->Draw("Assets/layout/practice_intro.txt", "white", 19, 7);
	mConsole->Draw("Typing Practice", "white", mXPosTitleStart + 2, mYPosTitleStart);
	mConsole->Draw("Long", "yellow", mXPosTitleStart + 7, mYPosTitleStart + 2);

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
}


///////////////
/* 타자 연습 */
///////////////
void LongPractice::RenderPractice()
{
	string presetCode;			// 전체 프리셋 코드
	string presetLine;			// 프리셋 라인 
	string presetLineOrganized;	// 프리셋 라인 코드화
	string userLine;			// 유저 입력 라인
	string userLineOrganized;	// 유저 입력 라인 코드화
	size_t indentation;			// 들여쓰기
	size_t CurrentIndentation;	// 현재 들여쓰기 수
	size_t prePos, pos;
	size_t currentLine;

	mTimer->Reset();
	mKeyboard->Clear();
	mConsole->Clear();
	mConsole->Draw("Assets/layout/practice_main.txt", "white", 0, 1);

	mPresetTotalCh = 0;	// 프리셋 문자 수
	mUserTotalCh = 0;	// 사용자 문자 수
	mUserWrongCh = 0;	// 오타 문자 수

	for (int testNum = 0; testNum < mTestCase; testNum++)
	{
		presetCode = GetRandomText("long").GetText();										// 무작위 프리셋 코드로 설정

		mConsole->Draw(presetCode, "white", mXPosPresetCodeStart, mYPosPresetCodeStart);	// 프리셋 코드 출력

		pos = 0;
		prePos = 0;

		for (currentLine = 0; (pos = presetCode.find('\n', pos + 1)) < presetCode.size(); currentLine++)
		{
			presetLine = presetCode.substr(prePos, pos - prePos);											// 프리셋의 한 줄 추출
			mConsole->Draw(presetLine, "yellow", mXPosPresetCodeStart, mYPosPresetCodeStart + currentLine);	// 현재 입력해야 하는 줄이므로, 노락색으로 출력
			prePos = pos + 1;

			indentation = Whitespace(presetLine);	// 들여쓰기 계산
			presetLineOrganized = presetLine;		// 프리셋 코드 라인 복사
			OrganizeCode(presetLineOrganized);		// 프리셋 코드 라인 정리

			mConsole->Color("white");																// 콘솔 텍스트 색상 세팅
			mConsole->CursorPosition(mXPosUserCodeStart, mYPosUserCodeStart + currentLine);			// 사용자 입력 위치로 커서 이동

			for (CurrentIndentation = 0; CurrentIndentation < indentation; CurrentIndentation++)	// 들여쓰기 빈칸 삽입
				cout << " ";

			getline(cin, userLine);				// 사용자로부터 한 줄 읽기

			userLineOrganized = userLine;		// 사용자 코드 라인 복사
			OrganizeCode(userLineOrganized);	// 사용자 코드 라인 정리

			mPresetTotalCh += presetLineOrganized.size();						// 프리셋 문자 수 업데이트
			mUserTotalCh += userLineOrganized.size();							// 사용자 문자 수 업데이트
			mTypingSpeed = (int)(mUserTotalCh / mTimer->GetElapsedTime() * 60);	// 속도 업데이트

			if (presetLineOrganized == userLineOrganized)																// 정답
			{
				mConsole->Draw(userLine, "green", mXPosUserCodeStart + indentation, mYPosUserCodeStart + currentLine);	// 초록색으로 변경
				mConsole->Draw("Good", "green", mXPosCurrect, mYPosCurrect);											// 상태 메시지 출력
			}
			else																	// 오답
			{
				for (size_t count = 0; count < presetLineOrganized.size(); count++)	// 사용자 오타 문자 수 업데이트
				{
					if (count < userLine.size())									// 사용자 코드 라인 이내에서
					{
						if (userLine[count] != presetLineOrganized[count])			// 틀렸다면
							mUserWrongCh++;											// 오타 문자 수 증가
					}
					else															// 사용자 코드 라인 이외라면
						mUserWrongCh++;												// 오타 문자 수 증가
				}

				mConsole->Draw(userLine, "red", mXPosUserCodeStart + indentation, mYPosUserCodeStart + currentLine);
				mConsole->Draw("Bad ", "red", mXPosCurrect, mYPosCurrect);			// 빨간색으로 변경, 상태 메시지 출력
			}

			mTypingAccuracy = 100 - mUserWrongCh * 100 / mPresetTotalCh;						// 정확도 업데이트

			mConsole->Clear(mXPosSpeed, mYPosSpeed, 4, 1);										// 속도 상자 비우기
			mConsole->Clear(mXPosAccuracy, mYPosAccuracy, 4, 1);								// 정확도 상자 비우기
			mConsole->Draw(to_string(mTypingSpeed), "white", mXPosSpeed, mYPosSpeed);			// 속도 출력
			mConsole->Draw(to_string(mTypingAccuracy), "white", mXPosAccuracy, mYPosAccuracy);	// 정확도 출력
			mConsole->Draw(presetLine, "white", mXPosPresetCodeStart, mYPosPresetCodeStart + currentLine);	// 현재 프리셋 라인을 노란 색에서 흰 색으로 변경
		}

		mConsole->Clear(mXPosPresetCodeStart, mYPosPresetCodeStart, mWidthCodeBox, mHeightCodeBox);	// 프리셋 코드 상자 비우기
		mConsole->Clear(mXPosUserCodeStart, mYPosUserCodeStart, mWidthCodeBox, mHeightCodeBox);		// 사용자 코드 상자 비우기
	}

	mConsole->Clear();	// 콘솔 화면 비우기
	mKeyboard->Clear();	// 키보드 입력 초기화
}


///////////////
/* 종료 화면 */
///////////////
void LongPractice::RenderResult()
{
	mConsole->Clear();
	mKeyboard->Clear();

	mConsole->Draw("Assets/layout/practice_intro.txt", "white", 19, 7);
	mConsole->Draw("Speed : ", "white", mXPosTitleStart + 3, mYPosTitleStart);
	mConsole->CursorPosition(mXPosTitleStart + 11, mYPosTitleStart);

	if (mTypingSpeed >= mRecentSpeed.back())	// 마지막 기록보다 나아졌다면
		mConsole->Color("green");				// 다음 텍스트를 초록색으로 설정
	else mConsole->Color("red");				// 나빠졌다면 빨간색으로 설정

	cout << mTypingSpeed;						// 속도 출력
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

	for (;;)	// 종료 프롬프트
	{
		mConsole->Draw("* Press Enter to Quit *", "white", mXPosPrompt, mYPosPrompt);	// 엔터 프롬프트
		mConsole->Draw("y", "random", mXPosTrafficLight, mYPosTrafficLight);			// 전구 1
		mConsole->Draw("y", "random", mXPosTrafficLight + 6, mYPosTrafficLight);		// 전구 2
		mConsole->Draw("y", "random", mXPosTrafficLight + 12, mYPosTrafficLight);		// 전구 3
		Sleep(250);

		mKeyboard->DynamicInput();			// 동적 입력
		if (mKeyboard->IsPressed("enter"))	// 엔터가 입력되었다면
			break;							// 반복문 종료

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
/* 통계 파일 읽기 */
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
		mRecentAccuracy.push(stoi(numStr));	// 정확도를 큐에 추가
		fileSpeed >> numStr;
		mRecentSpeed.push(stoi(numStr));	// 속도를 큐에 추가
	}

	fileAccuracy.close();
	fileSpeed.close();
}


////////////////////
/* 통계 파일 쓰기 */
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

	if (mRecentResultNum == 5)	// 큐에 5개의 기록이 있다면
	{
		mRecentAccuracy.pop();	// 정확도 한 개 제거
		mRecentSpeed.pop();		// 속도 한 개 제거
	}

	mRecentAccuracy.push(mTypingAccuracy);	// 현재 정확도를 큐에 삽입
	mRecentSpeed.push(mTypingSpeed);		// 현재 속도를 큐에 삽입

	/* 큐의 정확도와 속도를 파일에 기록 */
	for (; mRecentAccuracy.size() > 1;)
	{
		fileAccuracy << mRecentAccuracy.front() << ' ';		// 차례대로 기록, 공백으로 구분
		fileSpeed << mRecentSpeed.front() << ' ';			//

		mRecentAccuracy.pop();	// 기록 후 제거
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
/* 들여쓰기 빈칸 계산 */
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
/* 코드 정리 */
///////////////
void LongPractice::OrganizeCode(string& currentLine)
{
	size_t i;

	/* 들여쓰기 계산 */
	for (i = 0; i < currentLine.size(); i++)
	{
		if (currentLine[i] != ' ' && currentLine[i] != '\t')
			break;
	}

	currentLine.erase(0, i);	// 들여쓰기 삭제

	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//	
	//        * 기본 구조 *        //	
	//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
	/*                              *
		1. 연산자 또는 기호 판별
		2. 앞뒤 칸의 공백 제거
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
/* 연산자 판별 */
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
/* 메인 */
//////////
void LongPractice::Main()
{
	ReadResultFile();	// 통계 파일 읽기

	RenderIntro();		// 시작 화면
	RenderPractice();	// 타자 연습
	RenderResult();		// 결과 화면

	WriteResultFile();	// 통계 파일 쓰기
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