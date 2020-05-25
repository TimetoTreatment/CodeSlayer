#include "WordPractice.h"

WordPractice* WordPractice::sInstance = nullptr;

WordPractice* WordPractice::Instance() {
	if (sInstance == nullptr) {
		sInstance = new WordPractice;
	}
	return sInstance;
}

void WordPractice::Release() {
	delete sInstance;
	sInstance = nullptr;
}
