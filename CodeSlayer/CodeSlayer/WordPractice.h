//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 단어 타자 연습
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. 개요
		- 단어 타자 연습 기능 제공

	2. 기능
		- 시작 화면과 결과 화면 출력
		- 단어 타자 연습 실행
*/

#pragma once
#include "TypingManager.h"


class WordPractice : protected TypingManager
{
private:

	WordPractice();
	~WordPractice();

	queue<int> mRecentAccuracy;	// 최근 타자 정확도 통계
	queue<int> mRecentSpeed;	// 최근 타자 속도 통계
	int mRecentResultNum = 0;

	const int mTestCase = 30;	// 반복 횟수

	/* 시작 화면 */
	void RenderIntro();

	/* 타자 연습 */
	void RenderPractice();

	/* 결과 화면 */
	void RenderResult();

	/* 통계 파일 읽기 */
	void ReadResultFile();

	/* 통계 파일 쓰기 */
	void WriteResultFile();

public:

	/* 메인 */
	void Main();


private:
	static WordPractice* sInstance;

public:
	static WordPractice* Instance();
	static void Release();
};
