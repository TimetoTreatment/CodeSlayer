//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 짧은 글 타자 연습
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. 개요
		- 짧은 글 타자 연습 기능 제공

	2. 기능
		- 시작 화면과 결과 화면 출력
		- 짧은 글 타자 연습 실행
*/

#pragma once
#include "TypingManager.h"


class ShortPractice : protected TypingManager
{
private:

	ShortPractice();
	~ShortPractice();

	queue<int> mRecentAccuracy;	// 최근 타자 정확도 통계
	queue<int> mRecentSpeed;	// 최근 타자 속도 통계
	int mRecentResultNum = 0;

	const int mTestCase = 10;	// 반복 횟수

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

	/* 코드 정리 */
	void OrganizeCode(string& currentLine);

	/* 연산자 판별 */
	bool IsOperator(char ch) const;

public:

	/* 메인 */
	void Main();


private:
	static ShortPractice* sInstance;

public:
	static ShortPractice* Instance();
	static void Release();
};
