#pragma once
class Statistics
{
private:



public:

	/* 메인 함수 */
	void Main();


private:
	static Statistics* sInstance;

public:
	static Statistics* Instance();
	static void Release();
};

