#include "Config.h"


void operator++(Screen& lhs, int)
{
	switch (lhs)
	{
	case Screen::MainMenu:		lhs = Screen::WordPractice;		break;
	case Screen::WordPractice:	lhs = Screen::ShortPractice;	break;
	case Screen::ShortPractice:	lhs = Screen::LongPractice;		break;
	case Screen::LongPractice:	lhs = Screen::MiniGame;			break;
	case Screen::MiniGame:		lhs = Screen::Statistics;		break;
	case Screen::Statistics:	lhs = Screen::Exit;				break;
	case Screen::Exit:			lhs = Screen::MainMenu;			break;
	}
}


void operator--(Screen& lhs, int)
{
	switch (lhs)
	{
	case Screen::Exit:			lhs = Screen::MiniGame;			break;
	case Screen::MiniGame:		lhs = Screen::LongPractice;		break;
	case Screen::LongPractice:	lhs = Screen::ShortPractice;	break;
	case Screen::ShortPractice:	lhs = Screen::WordPractice;		break;
	case Screen::WordPractice:	lhs = Screen::Statistics;		break;
	case Screen::Statistics:	lhs = Screen::MainMenu;			break;
	case Screen::MainMenu:		lhs = Screen::Exit;				break;
	}
}