#pragma once

class Key
{
public:

	static const int enter = 13;
	static const int arrow = 224;
	static const int up = 72;
	static const int down = 80;
	static const int left = 75;
	static const int right = 77;




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


class Max
{
public:

	static const int mNumWordText = 1;
	static const int mNumShortText = 1;
	static const int mNumLongText = 1;



};
