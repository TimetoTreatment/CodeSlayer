#include "Random.h"

std::random_device Random::mDevice;
std::mt19937 Random::mEngine(Random::mDevice());

int Random::Integer(int rangeStart, int rangeEnd)
{
	std::uniform_int_distribution<int> distribution(rangeStart, rangeEnd);
	return distribution(mEngine);
}


Random* Random::sInstance = nullptr;

Random* Random::Instance()
{
	if (sInstance == nullptr)
		sInstance = new Random;

	return sInstance;
}

void Random::Release()
{
	delete sInstance;
	sInstance = nullptr;
}