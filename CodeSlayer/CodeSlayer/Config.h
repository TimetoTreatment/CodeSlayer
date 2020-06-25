//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// ȯ�� ����
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. ����
		- ���α׷����� ����ϴ� ȯ�� ���� ����
		- ȯ�� ������ ���� ������ ��, ���� ������ �湮�� �ʿ䰡 ����

	2. ���
		- �� ������ �ؽ�Ʈ�� ���� ����
		- ��� Ŭ�������� ��ũ�� ��ȣ ����
*/

#pragma once


/* ���� ���� */
class FileNum
{
public:

	static const unsigned int Word = 50;
	static const unsigned int Short = 25;
	static const unsigned int Long = 10;
	static const unsigned int Game = 17;

};


/* ��ũ�� */
enum class Screen
{
	MainMenu,
	WordPractice,
	ShortPractice,
	LongPractice,
	MiniGame,
	Statistics,
	Exit,
};

void operator++(Screen& lhs, int);	// ���� �޴�
void operator--(Screen& lhs, int);	// ���� �޴�
