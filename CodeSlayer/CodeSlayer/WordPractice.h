//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// �ܾ� Ÿ�� ����
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. ����
		- �ܾ� Ÿ�� ���� ��� ����

	2. ���
		- ���� ȭ��� ��� ȭ�� ���
		- �ܾ� Ÿ�� ���� ����
*/

#pragma once
#include "TypingManager.h"


class WordPractice : protected TypingManager
{
private:

	WordPractice();
	~WordPractice();

	queue<int> mRecentAccuracy;	// �ֱ� Ÿ�� ��Ȯ�� ���
	queue<int> mRecentSpeed;	// �ֱ� Ÿ�� �ӵ� ���
	int mRecentResultNum = 0;

	const int mTestCase = 30;	// �ݺ� Ƚ��

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

public:

	/* ���� */
	void Main();


private:
	static WordPractice* sInstance;

public:
	static WordPractice* Instance();
	static void Release();
};
