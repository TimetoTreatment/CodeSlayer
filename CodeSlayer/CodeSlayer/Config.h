//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 환경 변수
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/*
	1. 개요
		- 프로그램에서 사용하는 환경 변수 선언
		- 환경 변수의 값을 변경할 때, 여러 문서를 방문할 필요가 없음

	2. 기능
		- 각 프리셋 텍스트의 개수 제공
		- 모든 클래스에서 스크린 번호 공유
*/

#pragma once


/* 파일 개수 */
class FileNum
{
public:

	static const unsigned int Word = 50;
	static const unsigned int Short = 25;
	static const unsigned int Long = 10;
	static const unsigned int Game = 17;

};


/* 스크린 */
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

void operator++(Screen& lhs, int);	// 다음 메뉴
void operator--(Screen& lhs, int);	// 이전 메뉴
