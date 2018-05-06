#pragma once
#include "proj.h"

class Dictionary
{
private:
	vector<string> wordlist;
public:
	Dictionary();
	vector<string> getWordFromFile(string filename);
	bool FoundWord(string palavra);
	friend class Board;
};