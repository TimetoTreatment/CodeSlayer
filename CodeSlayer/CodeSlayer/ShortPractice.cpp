#include "ShortPractice.h"

ShortPractice* ShortPractice::sInstance = nullptr;

ShortPractice* ShortPractice::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ShortPractice;
	}
	return sInstance;
}

void ShortPractice::Release() {
	delete sInstance;
	sInstance = nullptr;
}
