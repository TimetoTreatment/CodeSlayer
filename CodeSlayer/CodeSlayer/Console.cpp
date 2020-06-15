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
		int colorSet[5] = { 12, 10, 3, 13, 14 };
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

	SetConsoleTextAttribute(mHandleConsole, colorValue);
}


//////////////////////
/* Set Text Color */
//////////////////////
void Console::CursorPosition(int x, int y)
{
	SetConsoleCursorPosition(mHandleConsole, { (short)x, (short)y });
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
void Console::Draw(string str_or_file, const char* color, int startX, int startY)
{
	if (4 <= str_or_file.size() && str_or_file.substr(str_or_file.size() - 4) == ".txt")
	{
		string line;
		fstream file(str_or_file, ios_base::in);

		for (Color(color); !file.eof(); startY++)
		{
			getline(file, line);

			CursorPosition(startX, startY);
			cout << line;
		}

		file.close();
	}
	else
	{
		size_t pos = 0;
		size_t prePos = 0;

		Color(color);

		for (int count = 0; pos < str_or_file.size(); count++)
		{
			pos = str_or_file.find('\n', pos + 1);
			CursorPosition(startX, startY + count);
			cout << str_or_file.substr(prePos, pos - prePos) << '\n';
			prePos = pos + 1;
		}
	}

	CursorPosition(0, 44);
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
