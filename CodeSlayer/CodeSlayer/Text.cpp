#include <iostream>
#include "Text.h"
using namespace std;

Text::Text() {
	mLength = 0;
}


void Text::SetText(string text) {
	mText = text;
}

string Text::GetText() const {
	return mText;
}

void Text::SetTextLength(int length) {
	mLength = length;
}

int Text::GetTextLength() const {
	return mLength;
}
