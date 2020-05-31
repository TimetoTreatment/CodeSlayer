#include "Statistics.h"

void Statistics::setInfo(WordPractice *ins) {
	ofstream out("Assets/Statistics/Word_record.txt");
	out << (int)ins->typeSpeed << endl;
	out << (int)ins->typeaccuracy << endl;
}

void Statistics::setInfo(ShortPractice *ins) {
	ofstream out("Assets/Statistics/Short_record.txt");
	out << (int)ins->typeSpeed << endl;
	out << (int)ins->typeaccuracy << endl;
}

void Statistics::setInfo(LongPractice *ins) {
	ofstream out("Assets/Statistics/Long_record.txt");
	out << (int)ins->typeSpeed << endl;
	out << (int)ins->typeaccuracy << endl;
}

void Statistics::printStatus() {
	
}

Statistics* Statistics::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Statistics;
	}

	return sInstance;
}