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
		vector<Word> wordVec;
	public:
		Board();
		Board(int x, int y);
		void DrawBoard();
		int WordExistsInBoard(string word);
		int WordFits(int x, int y, int horientation, string word);
		void InsertWord(int x, int y, char Direction, string word);
		int WordMatchesWithOtherLetters(int x, int y, int horientation, string word);
		char** CreateBoardMatrix();
		friend class Dictionary;
};
