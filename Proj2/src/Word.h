#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Word {
private:
	int id;
	string word;
	pair<int, int> coords;
	int horientation;

public:
	Word();

	~Word();

	Word(int id, int x, int y, int horientation, string word);

	int getID() const;

	int getX() const;

	int getY() const;

	int getHorientation() const;

	string getWord() const;

	void setID(int ID);
};
