#include "Keyboard.h"

Keyboard::Keyboard()
{
	mLastKey = 0;
}


///////////////
/* ���� �Է� */
///////////////
void Keyboard::StaticInput()
{
	mLastKey = _getch();			// Ű���� �Է� ���

	if (mLastKey == mKey["arrow"])	// ȭ��ǥ���
		mLastKey = _getch();		// �Է� ������Ʈ
}


///////////////
/* ���� �Է� */
///////////////
void Keyboard::DynamicInput()
{
	if (_kbhit())						// Ű���� �Է� ����
	{
		mLastKey = _getch();			// ���� ���� �Է°� ����

		if (mLastKey == mKey["arrow"])
			mLastKey = _getch();
	}
}


///////////////
/* �Է� Ȯ�� */
///////////////
bool Keyboard::IsPressed(string key)
{
	if (mLastKey == mKey[key])	// ������ Ű�� �ԷµǾ��ٸ�
		return true;			// �� ��ȯ

	return false;
}


/////////////////
/* �Է� �ʱ�ȭ */
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