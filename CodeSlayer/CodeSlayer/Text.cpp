#include <iostream>
#include "Text.h"
using namespace std;

Text::Text() {
	textLength = 0;
}


void Text::SetText(string t) {
	text = t;
}

string Text::GetText() const {
	return text;
}

void Text::SetTextLength(int tl) {
	textLength = tl;
}

int Text::GetTextLength() const {
	return textLength;
}
