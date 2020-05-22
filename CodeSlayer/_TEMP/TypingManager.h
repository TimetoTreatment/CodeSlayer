#pragma once
#include <iostream>
#include "Text.h"
#include "Config.h"
#include "Random.h"
#include <fstream>
#include <string>

using namespace std;

class TypingManager {

private:

	vector<Text> Words;
	vector<Text> Shorts;
	vector<Text> Longs;
	/*
	type 1 = word
	type 2 = short
	type 3 = long
	*/

public:
	Text GetRandomText(int type);

	void readFile();

private:
	static TypingManager* sinstance;
	
public:
	static TypingManager* instance();
	static void release();
	
};
