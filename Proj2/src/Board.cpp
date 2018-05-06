#include "Board.h"

Board::Board()
{
	xSize = 0;
	ySize = 0;
}

Board::Board(int xSize, int ySize)
{
	this->xSize = xSize;
	this->ySize = ySize;
	InitializeBoard();
}

void Board::DrawBoard() 
{
	cout << " ";
	int asciiValue = 97;
	for (int i = 0; i < xSize; i++) {

		cout << " " << char(asciiValue);
		asciiValue++;
	}

	cout << endl;
	asciiValue = 65;
	for (int i = 0; i < ySize; i++) {
		cout << char(asciiValue);
		asciiValue++;
		for (int j = 0; j < xSize; j++) {
			cout << " " << BoardArray[i][j]; //TODO: Replace with array of the board
		}
		cout << endl;
	}

}



void Board::InsertWord(int x, int y, char Direction, string word) 
{

	Dictionary a;
	a.getWordFromFile("dicionario.txt");
	if (a.FoundWord(word) == false) {
		cout << " The word isn't in the dictionary" << endl;
		return;
	}

	if (Direction == 'V' || Direction == 'v')
	{
		for (unsigned int i = y; i < word.size(); i++)
		{
			char a = word.at(i);
			BoardArray[i][y] = a;
		}
	}



	else if (Direction == 'H' || Direction == 'h')
	{
		for (unsigned int i = x; i < word.size(); i++)
		{
			char a = word.at(i);
			BoardArray[x][i] = a;
		}
	}




	else
	{
		cout << " The direction is incorrect! " << endl;
		return;
	}
}

void Board::InitializeBoard(){
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			BoardArray[i][j] = '*';
		}
	}
}
