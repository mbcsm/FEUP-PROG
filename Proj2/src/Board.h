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
public:
	Board();
	Board(int x, int y);
	int getEndGame();
	void DrawBoard();
	int WordExistsInBoard(string word);
	int WordFits(int x, int y, int horientation, string word);
	void InsertWord(int x, int y, char Direction, string word);
	int WordMatchesWithOtherLetters(int x, int y, int horientation, string word);
	int WordBlackCells(char** BoardArray);
	char** CreateBoardMatrix();
	int CheckEndGame();
	friend class Dictionary;
	vector<string> WordsThatFit(int x, int y, int horientation);
	void SaveToFile(string outputfile);
	void removeWord(string word);
};
