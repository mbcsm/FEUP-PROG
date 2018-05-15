#include "Word.h"

Word::Word(int id, int x, int y, int horientation, string word, bool hidden) {
	this->id = id;
	this->coords.first = x;
	this->coords.second = y;
	this->horientation = horientation;
	this->word = word;
	this->hidden = hidden;
}

Word::~Word() {
}

void Word::setID(int id) {
	this->id = id;
}

int Word::getID() const {
	return this->id;
}

int Word::getX() const {
	return this->coords.first;
}

int Word::getY() const {
	return this->coords.second;
}

bool Word::isHidden() const {
	return this->hidden;
}

int Word::getHorientation() const {
	return this->horientation;
}

string Word::getWord() const {
	return this->word;
}
