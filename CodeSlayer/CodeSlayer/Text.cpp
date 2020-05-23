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

void Text::IsUsed() { // ���ھ��� �Լ� ȣ��Ǹ� ���� ������ ����.
	isUsed = true;
}

bool Text::GetIsUsed() const {
	return isUsed;
}
