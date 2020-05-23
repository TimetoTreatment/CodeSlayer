#include "console.h"


//////////////////////////////////
/* Change Color Name to Integer */
//////////////////////////////////
int Console::ColorNameToNumber(const string& colorName) const
{
	if (colorName == "default")
		return -1;

	if (colorName == "random")
	{
		int colorSet[5] = { 12,10,3,13,14 };
		return colorSet[rand() % 5];
	}
	else if (colorName == "red")	return 12;	// RED
	else if (colorName == "green")	return 10;	// GREEN
	else if (colorName == "blue")	return 3;	// BLUE
	else if (colorName == "purple")	return 13;	// PURPLE
	else if (colorName == "yellow")	return 14;	// YELLOW
	else if (colorName == "white")	return 15;	// WHITE
	else if (colorName == "black")	return 0;	// BLACK
	return -1;
}


////////////////////
/* Set Text Color */
////////////////////

void Console::Color(const string& foreground, const string& background)
{
	int colorForeground = ColorNameToNumber(foreground);
	int colorBackground = ColorNameToNumber(background);
	int colorValue;

	if (colorForeground == -1) colorForeground = 7;			// Defalut value is 7
	if (colorBackground == -1) colorBackground = 0;			// Defalut value is 0
	colorValue = (colorBackground * 16) + colorForeground;

	SetConsoleTextAttribute(hConsole, colorValue);
}


//////////////////////
/* Set Text Color */
//////////////////////

void Console::CursorPosition(int x, int y)
{
	SetConsoleCursorPosition(hConsole, { (short)x, (short)y });
}


///////////////////////
/* Clear CMD Console */
///////////////////////
void Console::Clear()
{
	mEraser.resize(130, ' ');

	CursorPosition(0, 0);

	for (int count = 0; count < 45; count++)
		printf("%s\n", mEraser.c_str());

	CursorPosition(0, 0);
}


///////////////////////
/* Clear CMD Console */
///////////////////////
void Console::Clear(int startX, int startY, int width, int height)
{
	mEraser.resize(width, ' ');

	for (int count = 0; count < height; count++)
	{
		CursorPosition(startX, startY + count);
		printf("%s\n", mEraser.c_str());
	}
}


//////////////////////////////
/* Draw TXT File to Console */
//////////////////////////////
void Console::Draw(string file_or_str, const char* color, int startX, int startY)
{
	Color(color);

	if (file_or_str.substr(file_or_str.size() - 4) == ".txt")
	{
		string line;
		fstream file(file_or_str, ios_base::in);

		for (; !file.eof(); startY++)
		{
			getline(file, line);

			CursorPosition(startX, startY);
			cout << line;
		}

		file.close();
	}
	else
	{
		CursorPosition(startX, startY);
		cout << file_or_str;
	}
}


Console* Console::sInstance = nullptr;

Console* Console::Instance()
{
	if (sInstance == nullptr)
		sInstance = new Console;

	return sInstance;
}

void Console::Release()
{
	delete sInstance;
	sInstance = nullptr;
}
