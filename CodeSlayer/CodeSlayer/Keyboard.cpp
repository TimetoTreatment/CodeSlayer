#include "Keyboard.h"

Keyboard::Keyboard()
{
	mLastKey = 0;
}


///////////////
/* 정적 입력 */
///////////////
void Keyboard::StaticInput()
{
	mLastKey = _getch();			// 키보드 입력 대기

	if (mLastKey == mKey["arrow"])	// 화살표라면
		mLastKey = _getch();		// 입력 업데이트
}


///////////////
/* 동적 입력 */
///////////////
void Keyboard::DynamicInput()
{
	if (_kbhit())						// 키보드 입력 감지
	{
		mLastKey = _getch();			// 이하 정적 입력과 동일

		if (mLastKey == mKey["arrow"])
			mLastKey = _getch();
	}
}


///////////////
/* 입력 확인 */
///////////////
bool Keyboard::IsPressed(string key)
{
	if (mLastKey == mKey[key])	// 인자의 키가 입력되었다면
		return true;			// 참 반환

	return false;
}


/////////////////
/* 입력 초기화 */
/////////////////
void Keyboard::Clear()
{
	mLastKey = 0;
}


Keyboard* Keyboard::s_instance = nullptr;

Keyboard* Keyboard::Instance()
{
	if (s_instance == nullptr)
		s_instance = new Keyboard;

	return s_instance;
}

void Keyboard::Release()
{
	delete s_instance;
	s_instance = nullptr;
}