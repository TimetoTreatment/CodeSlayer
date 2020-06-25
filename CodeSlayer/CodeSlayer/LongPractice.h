//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// �� �� Ÿ�� ����
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. ����
		- �� �� Ÿ�� ���� ��� ����

	2. ���
		- ���� ȭ��� ��� ȭ�� ���
		- �� �� Ÿ�� ���� ����
		- �ڵ� ���� �� ���� �Ǻ�
*/

#pragma once
#include "TypingManager.h"


class LongPractice : protected TypingManager
{
private:

	LongPractice();
	~LongPractice();

	queue<int> mRecentAccuracy;	// �ֱ� Ÿ�� ��Ȯ�� ���
	queue<int> mRecentSpeed;	// �ֱ� Ÿ�� �ӵ� ���
	int mRecentResultNum = 0;

	const int mTestCase = 3;	// �ݺ� Ƚ��

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

	/* �鿩���� ��ĭ ��� */
	size_t Whitespace(const string& currentLine) const;

	/* �ڵ� ���� */
	void OrganizeCode(string& currentLine);

	/* ������ �Ǻ� */
	bool IsOperator(char ch) const;

public:

	/* ���� */
	void Main();


private:
	static LongPractice* sInstance;

public:
	static LongPractice* Instance();
	static void Release();
};
