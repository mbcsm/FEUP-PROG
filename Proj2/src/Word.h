#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Word {
private:
	int id;
	string word;
	bool hidden;
	pair<int, int> coords;
	int horientation;

public:
	//Word();

	~Word();

	Word(int id, int x, int y, int horientation, string word, bool hidden);

	int getID() const;

	int getX() const;

	int getY() const;

	bool isHidden() const;

	int getHorientation() const;

	string getWord() const;

	void setID(int ID);
};
