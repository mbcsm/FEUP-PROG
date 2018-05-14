#pragma once
#include "proj.h"
#include <iostream>
#include <vector>

class Dictionary
{
private:
	vector<string> wordlist;
public:
	Dictionary();
	vector<string> getWordFromFile(string filename);
	bool FoundWord(string palavra);
	string showSynonym(string palavra);
	friend class Board;
};
