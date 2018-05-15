#pragma once
#include <vector>
#include <iterator>

#include "Word.h"
#include "Dictionary.h"
#include "Proj.h"

using namespace std;
class Board
{

private:
	int xSize;
	int ySize;
	int endGame = 0;
	vector<Word> wordVec;
	vector<Word> wordPlayerVec;
	bool playerMode;
public:
	Board();
	Board(int x, int y);
	int getEndGame();
	int getxSize();
	int getySize();
	vector<vector<string>> getwordVec();
	bool operator==(Board b);
	void DrawBoard();
	int WordExistsInBoard(string word);
	int WordFits(int x, int y, int horientation, string word);
	void InsertWord(int x, int y, char Direction, string word, bool showWords);
	int WordMatchesWithOtherLetters(int x, int y, int horientation, string word);
	int WordBlackCells(char** BoardArray);
	char** CreateBoardMatrix();
	int CheckEndGame();
	friend class Dictionary;
	vector<string> WordsThatFit(int x, int y, int horientation);
	void SaveToFile(string outputfile, vector<string> position);
	void removeWord(string word);
	void loadBoard(string filename, bool showWords);
	void showClues();
};
