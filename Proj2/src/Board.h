#pragma once
#include "Dictionary.h"
#include "Proj.h"

class Board
{
	
	private:
		int xSize;
		int ySize;
		char BoardArray[100][100];
	public:
		Board();
		Board(int x, int y);
		void DrawBoard();
		void InitializeBoard();
		void InsertWord(int x, int y, char Direction, string word);
		friend class Dictionary;
};
