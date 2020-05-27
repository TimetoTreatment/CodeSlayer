#pragma once
class Statistics
{
private:



public:



private:
	static Statistics* sInstance;

public:
	static Statistics* Instance();
	static void Release();
};

