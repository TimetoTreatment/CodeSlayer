#pragma once

class FileNum
{
public:

	static const unsigned int Word = 50;
	static const unsigned int Short = 25;
	static const unsigned int Long = 10;
	static const unsigned int Game = 16;

};


enum class Screen
{
	MainMenu,
	WordPractice,
	ShortPractice,
	LongPractice,
	MiniGame,
	Exit,
};

void operator++(Screen& lhs, int);
void operator--(Screen& lhs, int);