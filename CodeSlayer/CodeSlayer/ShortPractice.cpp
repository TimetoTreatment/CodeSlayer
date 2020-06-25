#include "ShortPractice.h"


ShortPractice::ShortPractice()
{

}


ShortPractice::~ShortPractice()
{

}


///////////////
/* 시작 화면 */
///////////////
void ShortPractice::RenderIntro()
{
	mConsole->Draw("Assets/layout/practice_intro.txt", "white", 19, 7);
	mConsole->Draw("Typing Practice", "white", mXPosTitleStart + 2, mYPosTitleStart);
	mConsole->Draw("Short", "green", mXPosTitleStart + 7, mYPosTitleStart + 2);

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


void ShortPractice::RenderPractice()
{
	string presetCode;	// 프리셋 코드
	string userCode;	// 사용자 코드
	int currentWord;
	int testPageNum = (mTestCase - 1) / 5 + 1;

	mTimer->Reset();
	mKeyboard->Clear();
	mConsole->Clear();
	mConsole->Draw("Assets/layout/practice_main.txt", "white", 0, 1);

	mPresetTotalCh = 0;	// 프리셋 문자 수
	mUserTotalCh = 0;	// 사용자 문자 수
	mUserWrongCh = 0;	// 오타 문자 수

	for (int testPageCount = 0; testPageCount < testPageNum; testPageCount++)
	{
		for (currentWord = 0; currentWord < 5 && testPageCount * 5 + currentWord < mTestCase; currentWord++)
		{
			presetCode = GetRandomText("short").GetText();

			mConsole->Draw(presetCode, "yellow", mXPosPresetCodeStart, mYPosPresetCodeStart + currentWord * 3);	// 현재 입력해야 하는 단어를 노란색으로 변경

			mConsole->Color("white");																// 콘솔 텍스트 색상 세팅
			mConsole->CursorPosition(mXPosUserCodeStart, mYPosUserCodeStart + currentWord * 3);		// 사용자 입력 위치로 커서 이동

			getline(cin, userCode);					// 한 줄 읽기

			mPresetTotalCh += presetCode.size();	// 프리셋 문자 수 업데이트
			mUserTotalCh += userCode.size();		// 사용자 문자 수 업데이트

			mTypingSpeed = (int)(mUserTotalCh / mTimer->GetElapsedTime() * 60);		// 속도 업데이트

			if (presetCode == userCode)																			// 정답
			{
				mConsole->Draw(userCode, "green", mXPosUserCodeStart, mYPosUserCodeStart + currentWord * 3);	// 초록색으로 변경
				mConsole->Draw("Good", "green", mXPosCurrect, mYPosCurrect);									// 상태 메시지 출력
			}
			else															// 오답
			{
				for (size_t count = 0; count < presetCode.size(); count++)	// 사용자 오타 문자 수 업데이트
				{
					if (count < userCode.size())							// 사용자 코드 라인 이내에서
					{
						if (userCode[count] != presetCode[count])			// 틀렸다면
							mUserWrongCh++;									// 오타 문자 수 증가
					}
					else													// 사용자 코드 라인 이외라면
						mUserWrongCh++;										// 오타 문자 수 증가
				}

				mConsole->Draw(userCode, "red", mXPosUserCodeStart, mYPosUserCodeStart + currentWord * 3);
				mConsole->Draw("Bad ", "red", mXPosCurrect, mYPosCurrect);	// 빨간색으로 변경, 상태 메시지 출력
			}

			mTypingAccuracy = 100 - mUserWrongCh * 100 / mPresetTotalCh;	// 정확도 업데이트

			mConsole->Clear(mXPosSpeed, mYPosSpeed, 4, 1);														// 속도 상자 비우기
			mConsole->Clear(mXPosAccuracy, mYPosAccuracy, 4, 1);												// 정확도 상자 비우기
			mConsole->Draw(to_string(mTypingSpeed), "white", mXPosSpeed, mYPosSpeed);							// 속도 출력
			mConsole->Draw(to_string(mTypingAccuracy), "white", mXPosAccuracy, mYPosAccuracy);					// 정확도 출력
			mConsole->Draw(presetCode, "white", mXPosPresetCodeStart, mYPosPresetCodeStart + currentWord * 3);	// 현재 프리셋 단어를 노란 색에서 흰 색으로 변경 
		}

		mConsole->Clear(mXPosPresetCodeStart, mYPosPresetCodeStart, mWidthCodeBox, mHeightCodeBox);	// 프리셋 코드(단어) 상자 비우기
		mConsole->Clear(mXPosUserCodeStart, mYPosUserCodeStart, mWidthCodeBox, mHeightCodeBox);		// 유저 코드(단어) 상자 비우기
	}

	mConsole->Clear();
	mKeyboard->Clear();
}


///////////////
/* 종료 화면 */
///////////////
void ShortPractice::RenderResult()
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
void ShortPractice::WriteResultFile()
{
	fstream fileAccuracy("Assets/statistics/shortaccuracy.txt", ios::out);
	fstream fileSpeed("Assets/statistics/shortspeed.txt", ios::out);

	if (fileAccuracy.fail() || fileSpeed.fail())
	{
		cout << "ERROR : ShortPractice::WriteResultFIle()\n";
		exit(-1);
	}

	if (mRecentResultNum == 5)	// 큐에 5개의 기록이 있다면
	{
		mRecentAccuracy.pop();	// 정확도 한 개 제거
		mRecentSpeed.pop();		// 속도 한 개 제거
	}

	mRecentAccuracy.push(mTypingAccuracy);	// 현재 정확도를 큐에 삽입
	mRecentSpeed.push(mTypingSpeed);		// 현재 속도를 큐에 삽입

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


void ShortPractice::Main()
{
	ReadResultFile();	// 통계 파일 읽기

	RenderIntro();		// 시작 화면
	RenderPractice();	// 타자 연습
	RenderResult();		// 결과 화면

	WriteResultFile();	// 통계 파일 쓰기
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