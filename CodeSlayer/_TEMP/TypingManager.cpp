#include "TypingManager.h"


Text TypingManager::GetRandomText(int type) {
	/*
	type 1 = word
	type 2 = short
	type 3 = long
	*/
	int ran;

	if (type == 1) {
		ran = Random::Integer(0, FileNum::Word - 1);

		while (Words[ran].GetIsUsed())
			ran = Random::Integer(0, FileNum::Word - 1);

		Words[ran].IsUsed();

		return Words[ran];
	}
	else if (type == 2) {
		ran = Random::Integer(1, FileNum::Short);

		if ((sinstance->Shorts).at(ran).GetIsUsed()) {
			(sinstance->Shorts).at(ran).IsUsed();
			return (sinstance->Shorts).at(ran);
		}
		else {
			return sinstance->GetRandomText(2);
		}
	}
	else if (type == 3) {
		ran = Random::Integer(1, FileNum::Long);

		if ((sinstance->Longs).at(ran).GetIsUsed()) {
			(sinstance->Longs).at(ran).IsUsed();
			return (sinstance->Longs).at(ran);
		}
		else {
			return sinstance->GetRandomText(3);
		}
	}
}

void TypingManager::readFile() {

	ifstream txt;
	Text tmp;
	string str;

	txt.open("words.txt");
	if (txt.is_open()) {

		for (int i = 0; FileNum::Word > i; i++) {
			getline(txt, str);
			tmp.SetText(str);
			tmp.SetTextLength(str.length());
			Words.push_back(tmp);
		}

	}
	txt.close();

	txt.open("shorts.txt");
	if (txt.is_open()) {

		for (int i = 0; FileNum::Short > i; i++) {
			getline(txt, str);
			tmp.SetText(str);
			tmp.SetTextLength(str.length());
			(sinstance->Shorts).push_back(tmp);
		}
	}
	txt.close();

	string path = "long";
	for (int i = 0; FileNum::Long > i; i++) {
		str = path;
		str += i + '0';
		str += "txt";
		txt.open(str);
		if (txt.is_open()) {

			string tmpstr = "";

			while (!txt.eof()) {

				string temp;
				getline(txt, temp);
				tmpstr += temp;
				tmpstr += '\n';
			}

			tmp.SetText(tmpstr);
			tmp.SetTextLength(tmpstr.length());
			(sinstance->Longs).push_back(tmp);
		}
		txt.close();
	}
}

TypingManager* TypingManager::sinstance = nullptr;

TypingManager* TypingManager::instance() {
	if (sinstance == nullptr)
		sinstance = new TypingManager;

	return sinstance;
}

void TypingManager::release() {
	delete sinstance;
	sinstance = nullptr;
}



