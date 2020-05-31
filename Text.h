#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Text {

private:

	string text;
	int textLength;
	bool isUsed;

public:

	Text();

	void SetText(string t);
	string GetText() const;
	void SetTextLength(int tl);
	int GetTextLength() const;
	void IsUsed();
	bool GetIsUsed() const;
};