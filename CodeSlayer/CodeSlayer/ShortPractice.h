//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// ª�� �� Ÿ�� ����
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. ����
		- ª�� �� Ÿ�� ���� ��� ����

	2. ���
		- ���� ȭ��� ��� ȭ�� ���
		- ª�� �� Ÿ�� ���� ����
*/

#pragma once
#include "TypingManager.h"


class ShortPractice : protected TypingManager
{
private:

	ShortPractice();
	~ShortPractice();

	queue<int> mRecentAccuracy;	// �ֱ� Ÿ�� ��Ȯ�� ���
	queue<int> mRecentSpeed;	// �ֱ� Ÿ�� �ӵ� ���
	int mRecentResultNum = 0;

	const int mTestCase = 10;	// �ݺ� Ƚ��

	/* ���� ȭ�� */
	void RenderIntro();

	/* Ÿ�� ���� */
	void RenderPractice();

	/* ��� ȭ�� */
	void RenderResult();

	/* ��� ���� �б� */
	void ReadResultFile();

	/* ��� ���� ���� */
	void WriteResultFile();

	/* �ڵ� ���� */
	void OrganizeCode(string& currentLine);

	/* ������ �Ǻ� */
	bool IsOperator(char ch) const;

public:

	/* ���� */
	void Main();


private:
	static ShortPractice* sInstance;

public:
	static ShortPractice* Instance();
	static void Release();
};
