#include "Statistics.h"

Statistics* Statistics::sInstance = nullptr;

Statistics* Statistics::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Statistics;
	}
	return sInstance;
}

void Statistics::Release() {
	delete sInstance;
	sInstance = nullptr;
}
