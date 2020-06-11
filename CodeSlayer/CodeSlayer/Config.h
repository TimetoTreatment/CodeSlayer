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

void operator++(Screen& lhs, int);
void operator--(Screen& lhs, int);


