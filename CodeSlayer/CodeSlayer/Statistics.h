#pragma once
class Statistics
{
private:



public:

	/* ���� �Լ� */
	void Main();


private:
	static Statistics* sInstance;

public:
	static Statistics* Instance();
	static void Release();
};

