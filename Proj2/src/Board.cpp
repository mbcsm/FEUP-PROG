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
}

void Board::DrawBoard() 
{

	char BoardArray[100][100];

	for(int i = 0; i < 100; i++)
		for(int j = 0; j < 100; j++)
			BoardArray[i][j]='*';

	for(std::vector<int>::size_type i = 0; i != wordVec.size(); i++){
		if (wordVec[i].getHorientation() == 0){
			for (unsigned int j = 0; j < wordVec[i].getWord().size(); j++)
			{
				char a = wordVec[i].getWord().at(j);
				BoardArray[j + wordVec[i].getX()][wordVec[i].getY()] = a;
			}
		}
		else if (wordVec[i].getHorientation() == 1){
			for (unsigned int j = 0; j < wordVec[i].getWord().size(); j++)
			{
				char a = wordVec[i].getWord().at(j);
				BoardArray[wordVec[i].getX()][j + wordVec[i].getY()] = a;
			}
		}
	}

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
	int horientation = -1;
	if (Direction == 'V' || Direction == 'v')
		horientation = 0;
	else if (Direction == 'H' || Direction == 'h')
		horientation = 1;
	else
	{
		cout << " The direction is incorrect! " << endl;
		return;
	}


	Dictionary a;
	a.getWordFromFile("dicionario.txt");
	if (a.FoundWord(word) == false) {
		cout << " The word isn't in the dictionary" << endl;
		return;
	}
	if(WordExistsInBoard(word) == 1){
		cout << " Word Already Played" << endl;
		return;
	}
	if(WordFits(x, y, horientation, word) == 1){
		cout << " Word Doesn't Fit" << endl;
		return;
	}


	Word newWord = Word(wordVec.size(), x, y, horientation, word);
	wordVec.push_back(newWord);

}


int Board::WordExistsInBoard(string word){
	for(std::vector<int>::size_type i = 0; i != wordVec.size(); i++)
		if(wordVec[i].getWord() == word)
			return 1;

	return 0;
}

int Board::WordFits(int x, int y, int horientation, string word){
	if(x >= xSize || y >= ySize)
		return 1;

	if(horientation == 0)
		if(x + word.size() > xSize)
			return 1;
	if(horientation == 1)
		if(y + word.size() > ySize)
			return 1;

	return 0;
}

















