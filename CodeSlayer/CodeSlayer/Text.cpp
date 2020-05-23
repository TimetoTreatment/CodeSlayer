#include <iostream>
#include "Text.h"
using namespace std;

Text::Text() {
	isUsed = false;
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

void Text::IsUsed() { // 인자없이 함수 호출되면 사용된 것으로 간주.
	isUsed = true;
}

bool Text::GetIsUsed() const {
	return isUsed;
}
