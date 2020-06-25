//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 긴 글 타자 연습
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. 개요
		- 긴 글 타자 연습 기능 제공

	2. 기능
		- 시작 화면과 결과 화면 출력
		- 긴 글 타자 연습 실행
		- 코드 정리 후 정답 판별
*/

#pragma once
#include "TypingManager.h"


class LongPractice : protected TypingManager
{
private:

	LongPractice();
	~LongPractice();

	queue<int> mRecentAccuracy;	// 최근 타자 정확도 통계
	queue<int> mRecentSpeed;	// 최근 타자 속도 통계
	int mRecentResultNum = 0;

	const int mTestCase = 3;	// 반복 횟수

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

	/* 들여쓰기 빈칸 계산 */
	size_t Whitespace(const string& currentLine) const;

	/* 코드 정리 */
	void OrganizeCode(string& currentLine);

	/* 연산자 판별 */
	bool IsOperator(char ch) const;

public:

	/* 메인 */
	void Main();


private:
	static LongPractice* sInstance;

public:
	static LongPractice* Instance();
	static void Release();
};
