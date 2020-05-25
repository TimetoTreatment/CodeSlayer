#include "LongPractice.h"

LongPractice* LongPractice::sInstance = nullptr;

LongPractice* LongPractice::Instance() {
	if (sInstance == nullptr) {
		sInstance = new LongPractice;
	}

	return sInstance;
}

void LongPractice::Release() {
	delete sInstance;
	sInstance = nullptr;
}